//
// Created by Ayush Pandey on 30/11/2022.
//

#ifndef STMBENCH_INTERVAL_H
#define STMBENCH_INTERVAL_H

#include <vector>
#include <stdlib.h>
#include<algorithm>
#include <pthread.h>
#include "parameters.h"
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


using namespace std;


#define S 64
#define leafNodes = 300;
class interval{

public: double pre, post;
    int mode;
    long MySeq;
    interval( long a, long b, int m){
        pre = a; post = b; mode = m;
    }
};


//**************************************************************************************************************
class IntervalCheck{
public:
    interval *Array[S];
    int VectorSize[S];
    //Lock variable, one per lock-pool location
    pthread_rwlock_t ArrayLock[S];

    pthread_mutex_t mutex;
    long Seq;
    //Lock pool for Multi-DomLock, .i.e., multiple lock node per thread
    std::chrono::duration<long double, std::nano> Totalidleness[S];
    std::chrono::duration<long double, std::nano> modificationTimeDom;

    //Sequence number per thread for fairness and less contention
    int MySeq[S];

    //*****************************************************************************
    //Constructor for initialization of class variables
    //*****************************************************************************
    IntervalCheck()
    {
        Seq = 0;
        for(int i = 0;i<S; i++)
        {

            Array[i] = nullptr;
            pthread_rwlock_t ArrayLock[i];
        }
    }

    bool IsOverlap(interval *inv, int m, int threadID)
    {
        //cout<<"m=1";
        pthread_mutex_lock(&mutex);
        inv->MySeq = ++Seq;
        Array[threadID] = inv;
        pthread_mutex_unlock(&mutex);
        auto t1 = std::chrono::high_resolution_clock::now();
        for(int i=0; i< S; i++)
        {
            if(Array[i] != nullptr && i!=threadID)
            {
                interval *ptr = Array[i];
                //wait untill there is an overlap and my sequence number is greater
                while(ptr != nullptr &&
                    (inv->mode==1 || (inv->mode == 0 && ptr->mode == 1)) &&
                    ((ptr->pre <= inv->post && ptr->post>= inv->post) || (ptr->post >= inv->pre && ptr->pre<=inv->pre))
                      && ptr->MySeq < inv->MySeq)
                {
                    ptr = Array[i];
                }
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        Totalidleness[threadID] += t2-t1;
        return false;
    }

    void Delete(int index)
    {

        Array[index] = nullptr;


    }
};



#endif //STMBENCH_INTERVAL_H
