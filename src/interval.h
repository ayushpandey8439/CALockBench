//
// Created by Ayush Pandey on 30/11/2022.
//

#ifndef STMBENCH_INTERVAL_H
#define STMBENCH_INTERVAL_H

#include <vector>
#include <stdlib.h>
#include<algorithm>
#include <pthread.h>

using namespace std;
#define S 40
#define leafNodes = 300;

class interval{

public: double pre, post;
    int mode;
    long MySeq;
    interval( double a, double b, int m){
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
    vector<interval**>MultiLockPool;

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
        MultiLockPool.resize(S, nullptr);



    }

    bool IsOverlap(interval *inv, int m, int threadID)
    {
        //cout<<"m=1";
        pthread_mutex_lock(&mutex);
        inv->MySeq = ++Seq;
        Array[threadID] = inv;
        pthread_mutex_unlock(&mutex);

        for(int i=0; i< S; i++)
        {
            if(Array[i] != nullptr)
            {	interval *ptr = Array[i];
                //wait untill there is an overlap and my sequence number is greater
                while(ptr !=NULL &&
                (m == 1 || (m == 0 && ptr->mode == 1)) &&
                (ptr->pre <= inv->post && ptr->post >= inv->pre)
                && ptr->MySeq < inv->MySeq)
                {
                    ptr = Array[i];
                }

            }
        }

        return false;


    }

    void Delete(int index)
    {

        Array[index] = nullptr;


    }

    //*****************************************************************************
    //This function checks whether the multiple query nodes overlap with the lock pool
    //*****************************************************************************
    bool MultiOverlap(interval **QueryNodes, int Qsize, int m, int threadID)
    {

        VectorSize[threadID] = Qsize;

        pthread_mutex_lock(&mutex);
        MySeq[threadID] = ++Seq;
        MultiLockPool[threadID] = QueryNodes;
        pthread_mutex_unlock(&mutex);

        for(int i=0; i< S; i++)
        {
            interval** ptr = MultiLockPool[i];
            if(ptr != NULL)
            {
                for(int j=0;j<VectorSize[i];j++)
                {
                    for(int k=0;k<Qsize;k++)
                    {
                        while(ptr!=NULL && MySeq[threadID] > MySeq[i] && (m == 1 || (m == 0 && ptr[j]->mode == 1)) && ptr[j]->pre <= QueryNodes[k]->post && ptr[j]->post >= QueryNodes[k]->pre)
                        {
                            ptr = MultiLockPool[i];
                            if(ptr == NULL){
                                k = Qsize;
                                break;
                            }


                        }
                    }

                }
            }

        }


        return false;


    }


    //This function deletes the vector entry from MultiLockPool, i.e., UnLock
    void MultiDelete(int index)
    {


        MultiLockPool[index] = NULL;

    }
};



#endif //STMBENCH_INTERVAL_H
