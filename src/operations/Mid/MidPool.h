//
// Created by Ayush Pandey on 20/06/2024.
//

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

class midInterval{

public: int pre, post, rlm_pre, rlm_post, mode;
    midInterval( int a, int b, int c, int d, int m){
        pre = a; post = b; rlm_pre = c, rlm_post = d, mode = m;
    }
};

//**************************************************************************************************************
class MidPool{
public:
    midInterval *Array[SIZE];
    pthread_rwlock_t ArrayLock[SIZE];
    std::chrono::duration<long double, std::nano> idleness[SIZE];
    std::chrono::duration<long double, std::nano> modificationTime;
    atomic<long int> count = 1;

    MidPool()
    {
        for(int i = 0;i<SIZE; i++)
        {

            Array[i] = NULL;
            int ret =	pthread_rwlock_init(&(ArrayLock[i]), NULL); // Anju added the lock init
            if(ret != 0)
            {
                printf("***There is some problem in initializing the RW lock on the pool \n***");
            }
//		pthread_rwlock_t ArrayLock[i]; // Anju commented this local def by Saurabh.
        }

    }


/* The below function returns true if there is a path from cassm to a node with midInterval (min,max). */
    bool doesNodeReachInterval(ComplexAssembly *cassm, int min, int max )
    {
        Set<Assembly *> *subAssm = cassm->getSubAssemblies();
        SetIterator<Assembly *> iter = subAssm->getIter();
        bool childrenAreBase = cassm->areChildrenBaseAssemblies();
        while(iter.has_next())
        {
            Assembly *assm = iter.next();
            if((assm -> m_pre_number == min) && (assm -> m_post_number == max))
                return true; // The node with midInterval (min, max) is reachable from cassm.
            else if((assm -> m_pre_number <= min) && (assm -> m_post_number >= max))
            {
                bool isReachable;
                if(!childrenAreBase)
                    isReachable = doesNodeReachInterval((ComplexAssembly *)assm, min, max);
                else
                    isReachable = doesNodeReachInterval((BaseAssembly *)assm, min, max);
                if(isReachable)
                    return true;
            }
        }
        return false; // The node with midInterval (min, max) can not be reached from cassm.
    }

    bool doesNodeReachInterval(BaseAssembly *bassm, int min, int max )
    {
        BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
        while(iter.has_next())
        {
            CompositePart *cpart = iter.next();
            if(cpart -> m_pre_number == min && cpart -> m_post_number == max)
                return true;
        }
        return false;
    }

    DesignObj* findNodeWithInterval(ComplexAssembly *cassm,  int min, int max, int *nodeType)
    {
//    printf("Really Entered findNodeWithInterval for complex assem\n");
        if((cassm -> m_pre_number == min) && (cassm -> m_post_number == max) )
        {
            // This is the node with midInterval (min, max). Return it.
            *nodeType = 1; // 1 indicates complex assembly.
            //    printf("Found a complex assembly with midInterval (%d, %d). Returning.. \n", cassm -> m_pre_number, cassm -> m_post_number);
            return cassm;
        }
        else
        {
            // printf("Inside else part..\n");
            Set<Assembly *> *subAssm = cassm->getSubAssemblies();
            SetIterator<Assembly *> iter = subAssm->getIter();
            bool childrenAreBase = cassm->areChildrenBaseAssemblies();
            while(iter.has_next())
            {
                Assembly *assm = iter.next();
                if((assm -> m_pre_number <= min) && (assm -> m_post_number >= max) )
                {
                    if(!childrenAreBase)
                    {
                        return findNodeWithInterval((ComplexAssembly *)assm, min, max, nodeType);
                    }
                    else
                    {
                        return findNodeWithInterval((BaseAssembly *)assm, min, max, nodeType);
                    }
                }
            }
            *nodeType = 11; // Indicating invalid object
            return NULL;
        }

    }

    DesignObj* findNodeWithInterval(BaseAssembly *bassm,  int min, int max, int *nodeType)
    {
//  printf("Entered findNodeWithInterval for base assem\n");
        if((bassm -> m_pre_number == min) && (bassm -> m_post_number == max) )
        {
            // This is the node with midInterval (min, max). Return it.
            *nodeType = 2; // 2 indicates base assembly.
            //    printf("Found a base assembly with midInterval (%d, %d). Returning.. \n", bassm -> m_pre_number, bassm -> m_post_number);
            return bassm;
        }
        else
        {
//        *nodeType = 10; // Indicating invalid object
//      return NULL;
            BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
            while(iter.has_next())
            {
                CompositePart *cpart = iter.next();
                if((cpart -> m_pre_number == min) && (cpart->m_post_number == max))
                {
                    *nodeType = 3; // 3 indicates composite part.
                    return cpart;
                }
            }
        }
        // Code should not be reaching here. If it reaches, there is something wrong with the numbering.
        *nodeType = 10; // Indicating invalid object
        return NULL;
    }



    bool traverseAndCheckIfFS(int larger_min, int larger_max, int smaller_min, int smaller_max, DataHolder *dataHolder)
    {
//        printf("In operations.h..... Going to check FS on midIntervals (%d, %d) -- (%d, %d)\n", larger_min, larger_max, smaller_min, smaller_max);
        int nodeType;
        nodeType = 0;
        DesignObj* myObj = findNodeWithInterval(dataHolder->getModule()->getDesignRoot(), larger_min, larger_max, &nodeType);
        //      printf("NodeType = %d\n", nodeType);
        //    printf("Using DesignObj.... will it work???\n");
        //  printf("Trying.. (%d, %d)\n", myObj->m_pre_number, myObj->m_post_number);

        // We got the pointer to the node with the larger midInterval. Now do a level-by-level traversal to see if it is falsely subsuming the smaller midInterval.
        bool isReachable = false;
        if(nodeType == 1)
        {
            isReachable = doesNodeReachInterval((ComplexAssembly *)myObj, smaller_min, smaller_max );
        }
        else if(nodeType == 2)
        {
            isReachable = doesNodeReachInterval((BaseAssembly *)myObj, smaller_min, smaller_max );
        }

        if(isReachable)
        {
//            printf("Returning false --- from fn\n");
            return false; // smaller midInterval node is reachable. So not a false subsumption.
        }
        else
        {
            //          printf("Returning true *** from fn\n");
            return true; // It is a false subsumption.
        }
    }



// Anju edited this function to handle the read requests' overlap check.
    bool IsOverlap(midInterval *inv, int m, int threadID, DataHolder *dataHolder)
    {
        pthread_rwlock_wrlock(&ArrayLock[0]); // Taking the lock on the pool.
        totalLockAttempts++;
        for(int i=0; i< SIZE; i++)
        {
            if(Array[i] != NULL)
            {
                if((Array[i]->pre >= inv->pre && Array[i]->post <= inv->post) ||
                   (Array[i]->pre <= inv->pre && Array[i]->post >= inv->post))
                {
                    if(inv->mode == 0 && Array[i]->mode == 0)
                    {
                        continue; // The already locked midInterval and the current request are both in read mode. So this is NOT an actual overlap. We need to check if there is overlap with any other midInterval locked in write mode. So continuing the for loop.
                    }
                    else
                    {
                        // Check if the second numbering also says there is an overlap
                        if((Array[i]->rlm_pre >= inv->rlm_pre && Array[i]->rlm_post <= inv->rlm_post) || (Array[i]->rlm_pre <= inv->rlm_pre && Array[i]->rlm_post >= inv->rlm_post))
                        {
                            // Traverse and check if it is a false subsumption
                            bool isFS;
                            int larger_min, larger_max, smaller_min, smaller_max;
                            if((Array[i]->pre >= inv->pre && Array[i]->post <= inv->post))
                            {
                                larger_min = inv->pre; larger_max = inv->post; smaller_min = Array[i]->pre; smaller_max = Array[i]->post;
                            }
                            else
                            {
                                larger_min = Array[i]->pre; larger_max = Array[i]->post; smaller_min = inv->pre; smaller_max = inv->post;
                            }

                            isFS = traverseAndCheckIfFS(larger_min, larger_max, smaller_min, smaller_max, dataHolder);
                            if(isFS)
                            {
                                correctedFScountByTraversal++;
                                continue;
                            }
                            else
                            {
                                // True overlap
                                totalLockRejections++;
                                pthread_rwlock_unlock(&ArrayLock[0]); // Unlocking the pool before returning.
                                return true;
                            }
                        }
                        correctedFScountByMID++;
                    }
                }
            }
        }

        Insert(inv, threadID);
        pthread_rwlock_unlock(&ArrayLock[0]); // Unlocking the pool before returning.
        return false;

    }



    void Insert(midInterval *inv, int index)
    {

        //pthread_rwlock_wrlock(&ArrayLock[index]);
        Array[index] = inv;
        //pthread_rwlock_unlock(&ArrayLock[index]);

    }

    void Delete(int index)
    {//index=0;
        pthread_rwlock_wrlock(&ArrayLock[0]);

        Array[index] = NULL;
        pthread_rwlock_unlock(&ArrayLock[0]);


    }

};


#endif //SB7_LOCK_MIDPOOL_H
