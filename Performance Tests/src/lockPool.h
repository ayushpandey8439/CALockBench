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
#include "../../libraries/boost_1_81_0/boost/container/flat_set.hpp"

#define SIZE 256
using namespace std;
using namespace sb7;



class lockObject{
public:
    boost::container::flat_set<int>* criticalAncestors;
    int Id;
    int mode;
    long Oseq;

    lockObject(int pId, boost::container::flat_set<int> * ancestors, int m){
        Id = pId;
        criticalAncestors = ancestors;
        mode = m;
        Oseq=-1;
    }
};

class lockPool {
public:
    mutex lockPoolLock;
    lockObject* locks[SIZE];
    mutex threadMutexes[SIZE];
    shared_mutex threadGuards[SIZE];
    condition_variable threadConditions[SIZE];
    long int Gseq;

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
        for(int i=0;i< SIZE; i++){
            /// A thread won't run into conflict with itself.
            if(locks[i] != nullptr && i!= threadID){

                    /// Spin waiting on the condition.
                    auto l = locks[i];
                    while (l!= nullptr &&
                     /// If a read lock is requested for an object that is read locked, only then allow it.
                     (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                     /// Someone else has requested a lock on my LSCA before me.
                     (reqObj->Id == l->Id || reqObj->criticalAncestors->contains(l->Id) || l->criticalAncestors->contains(reqObj->Id)) &&
                     /// It isn't my turn to take the lock
                     (reqObj->Oseq > l->Oseq)) {
                        this_thread::yield();
                        l=locks[i];
                    }
            }
        }
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
