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

#define SIZE 256
using namespace std;
using namespace sb7;



class lockObject{
public:
    unordered_set<int>* criticalAncestors;
    int Id;
    int mode;
    long Oseq;

    lockObject(int pId, unordered_set<int> * ancestors, int m){
        Id = pId;
        criticalAncestors = ancestors;
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

    void waitResolve(int i, int threadID){
        /// Threads are blocked until the condition is true;
        abc:
        std::unique_lock<std::mutex> ul (threadMutexes[i]);
        bool waitstatus = threadConditions[i].wait_for(ul,1ms, [this, i, threadID] {
            return (locks[i] == nullptr ||
                    /// Read vs Read is not a conflict
                    (locks[threadID]->mode == 0 && locks[i]->mode == 0) ||
                    /// The hierarchies do not overlap
                    (locks[threadID]->Id != locks[i]->Id &&
                     !lscaHelpers::hasCriticalAncestor(locks[threadID]->criticalAncestors, locks[i]->Id)) ||
                    /// If all else fails, then at least it should be my turn.
                    locks[threadID]->Oseq <= locks[i]->Oseq);
        });
        if(!waitstatus) {
            goto abc;
        }
    }

    bool acquireLock(lockObject * reqObj, int threadID) {
        lockPoolLock.lock();
        reqObj->Oseq = ++Gseq;
        locks[threadID] = reqObj;
        lockPoolLock.unlock();
        for(int i=0;i< SIZE; i++){
            /// A thread won't run into conflict with itself.
            if(locks[i] != nullptr && i!= threadID){
                if(parameters.threadBlockingAllowed()) {
                    waitResolve(i, threadID);
                } else {
                    /// Spin waiting on the condition.
                    auto l = locks[i];
                    while (l!= nullptr &&
                     /// If a read lock is requested for an object that is read locked, only then allow it.
                     (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                     /// Someone else has requested a lock on my LSCA before me.
                     (reqObj->Id == l->Id || lscaHelpers::hasCriticalAncestor(reqObj->criticalAncestors, l->Id)) &&
                     /// It isn't my turn to take the lock
                     (reqObj->Oseq > l->Oseq)) {
                        if(processor_Count<parameters.getThreadNum()) this_thread::yield();
                        l=locks[i];
                    }
                }
            }
        }
        return true;
    }
    void releaseLock(lockObject *l, int threadId){
        if(parameters.threadBlockingAllowed()){
            {
                std::lock_guard<std::mutex> lk (threadMutexes[threadId]);
                locks[threadId] = nullptr;
            }
            threadConditions[threadId].notify_all();
        } else {
            locks[threadId] = nullptr;
        }
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
