
#ifndef SB7_LOCK_MIDPOOL_H
#define SB7_LOCK_MIDPOOL_H

#include <vector>
#include <stdlib.h>
#include<string>
#include <vector>
#include <pthread.h>
#include <chrono>
#include <atomic>

#include "../../struct/assembly.h"
#include "../../data_holder.h"
#define SIZE 256
extern int totalLockRejections;
extern int correctedFScountByTraversal;
extern int correctedFScountByMID;
extern int totalLockAttempts;
using namespace sb7;

class midInterval
{
public:
    long pre, post, rlm_pre, rlm_post;
    int mode;
    long MySeq;
    atomic_flag accessController = ATOMIC_FLAG_INIT;

    midInterval(long a, long b, long c, long d, int m)
    {
        pre = a;
        post = b;
        rlm_pre = c,
            rlm_post = d,
            mode = m;

        accessController.test_and_set();
    }
};

//**************************************************************************************************************

//**************************************************************************************************************
class MidPool
{
public:
    midInterval* Array[SIZE];
    int VectorSize[SIZE];
    atomic<long int> count = 1;
    //Lock variable, one per lock-pool location
    pthread_rwlock_t ArrayLock[SIZE];

    pthread_mutex_t mutex;
    long Seq;
    //Lock pool for Multi-DomLock, .i.e., multiple lock node per thread
    std::chrono::duration<long double, std::nano> idleness[SIZE];
    std::chrono::duration<long double, std::nano> modificationTime;
    //Sequence number per thread for fairness and less contention
    int MySeq[SIZE];

    //*****************************************************************************
    //Constructor for initialization of class variables
    //*****************************************************************************
    MidPool()
    {
        Seq = 0;
        for (int i = 0; i < SIZE; i++)
        {
            Array[i] = nullptr;
            pthread_rwlock_t ArrayLock[i];
        }
    }

    bool IsOverlap(midInterval* inv, int m, int threadID)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        //cout<<"m=1";
        pthread_mutex_lock(&mutex);
        inv->MySeq = ++Seq;
        Array[threadID] = inv;
        pthread_mutex_unlock(&mutex);

        for (int i = 0; i < SIZE; i++)
        {
            if (Array[i] != nullptr)
            {
                midInterval* ptr = Array[i];
                //wait untill there is an overlap and my sequence number is greater
                if (ptr != NULL &&
                    (m == 1 || (m == 0 && ptr->mode == 1)) &&
                    (ptr->post >= inv->pre && inv->post >= ptr->pre && ptr->rlm_post >= inv->rlm_pre && inv->rlm_post >=
                        ptr->rlm_pre) &&
                    //                      ((ptr->pre <= inv->post && ptr->post>= inv->post) || (ptr->post >= inv->pre && ptr->pre<=inv->pre))
                    ptr->MySeq < inv->MySeq)
                {
                    //                    ptr = Array[i];
                    ptr->accessController.wait(true);
                }
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        idleness[threadID] += (t2 - t1);
        return false;
    }

    void Delete(int index)
    {
        auto i = Array[index];
        i->accessController.clear();
        Array[index] = nullptr;
        i->accessController.notify_all();
    }
};


#endif
