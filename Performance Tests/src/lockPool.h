//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include <set>
#include <string>
#include <thread>         // std::thread
#include "data_holder.h"
#include "lscaHelpers.h"
#include "iostream"
#include "parameters.h"
#include <algorithm>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <shared_mutex>
#include "atomic"
#include "memory"
#include "chrono"

#define SIZE 64
using namespace std;
using namespace sb7;



class lockObject{
public:

    unordered_set<int> criticalAncestors;
    int Id;
    int mode;
    long Oseq;

    lockObject(int pId, unordered_set<int> * ancestors, int m){
        Id = pId;
        criticalAncestors.insert(ancestors->begin(), ancestors->end());
        mode = m;
        Oseq=-1;
    }
};

class lockPool {
public:
    const uint processor_Count = std::thread::hardware_concurrency();
    mutex lockPoolLock;
    lockObject* locks[SIZE];
    mutex threadMutexes[SIZE];
    shared_mutex threadGuards[SIZE];
    condition_variable threadConditions[SIZE];
    std::chrono::duration<long double, std::micro> idleness[SIZE];
    std::chrono::duration<long double, std::micro> modificationTimeCA;
    long int Gseq;
    ///CAnnot initialise here because the pool is created and initialised before the parameters are read from the console.
    //bool blockingAllowed = parameters.threadBlockingAllowed();

    lockPool(){
        Gseq = 0;
        for(int i=0; i<SIZE;i++)
        {
            locks[i] = nullptr;
        }
    }

    bool acquireLock(lockObject * reqObj, int threadID) {
        lockPoolLock.lock();
        reqObj->Oseq = ++Gseq;
        locks[threadID] = reqObj;
        lockPoolLock.unlock();
        auto t1 = std::chrono::high_resolution_clock::now();
        for(int i=0;i< SIZE; i++){
            /// A thread won't run into conflict with itself.
            /// Spin waiting on the condition.
            auto l = locks[i];
            while (l!= nullptr &&
             /// If a read lock is requested for an object that is read locked, only then allow it.
             (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
             /// Someone else has requested a lock on my LSCA before me (locked Sub-Hierarchy)or
             /// I am the LSCA of some node that is locked already (locked Super-hierarchy).
             (locks[threadID]->Id==l->Id ||
             l->criticalAncestors.contains(locks[threadID]->Id) ||
             locks[threadID]->criticalAncestors.contains(l->Id)) &&
             /// It isn't my turn to take the lock
             (reqObj->Oseq > l->Oseq)) {
                if(processor_Count<parameters.getThreadNum()) this_thread::yield();
                l=locks[i];
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        idleness[threadID] += t2-t1;
        return true;
    }

    void releaseLock(lockObject *l, int threadId){
        lockPoolLock.lock();
        locks[threadId] = nullptr;
        lockPoolLock.unlock();
    }
//
//    list<int> addToLockRequest(DataHolder*dh, list<int> & lockRequest, DesignObj & label){
//        if(lockRequest.empty()){
//            lockRequest = label.pathLabel;
//            return label.pathLabel;
//        } else {
//            list<int> common;
//            set_intersection(lockRequest.begin(), lockRequest.end(), label.begin(),label.end(), back_inserter(common));
//           return common;
//            auto it = lockRequest.begin();
//            while (it != lockRequest.end()) {
//                    if (!lscaHelpers::hasCriticalAncestor(&label.criticalAncestors, *it)) {
//                        it = lockRequest.erase(it);
//                    } else {
//                        ++it;
//                    }
//                }
//        }
//    }
};


#endif //STMBENCH_LOCKPOOL_H
