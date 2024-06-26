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
<<<<<<< HEAD
#include "chrono"
=======
#include "../../libraries/boost_1_81_0/boost/container/flat_set.hpp"
#include "pthread.h"
>>>>>>> blockingImplementation

#define SIZE 64
using namespace std;
using namespace sb7;



class lockObject{
public:
<<<<<<< HEAD

    unordered_set<int> criticalAncestors;
=======
    boost::container::flat_set<int>* criticalAncestors;
>>>>>>> blockingImplementation
    int Id;
    int mode;
    long Oseq;
    atomic_flag accessController = ATOMIC_FLAG_INIT;

    lockObject(int pId, boost::container::flat_set<int> * ancestors, int m){
        Id = pId;
        criticalAncestors.insert(ancestors->begin(), ancestors->end());
        mode = m;
        Oseq=-1;
        accessController.test_and_set();
    }
};

class lockPool {
public:
    const uint processor_Count = std::thread::hardware_concurrency();
    mutex lockPoolLock;
    lockObject* locks[SIZE];
<<<<<<< HEAD
    mutex threadMutexes[SIZE];
    shared_mutex threadGuards[SIZE];
    condition_variable threadConditions[SIZE];
    std::chrono::duration<long double, std::nano> idleness[SIZE];
    std::chrono::duration<long double, std::nano> modificationTimeCA;
=======
    shared_mutex threadMutexes[SIZE];
    condition_variable_any threadConditions[SIZE];
>>>>>>> blockingImplementation
    long int Gseq;
    std::chrono::duration<long double, std::nano> idleness[SIZE];
    std::chrono::duration<long double, std::nano> modificationTimeCA;
    atomic<long int> count = 1;
    const uint processor_Count = std::thread::hardware_concurrency();
    lockPool(){
        Gseq = 0;
        for(int i=0; i<SIZE;i++)
        {
            locks[i] = nullptr;
        }
    }

<<<<<<< HEAD
=======
    void waitResolve(int i, int threadID){
        /// Threads are blocked until the condition is true;
        std::shared_lock<shared_mutex> ul (threadMutexes[i]);
        threadConditions[i].wait(ul, [this, i, threadID] {
            return !(locks[i]!= nullptr &&
                 /// If a read lock is requested for an object that is read locked, only then allow it.
                 (locks[threadID]->mode == 1 || (locks[threadID]->mode==0 && locks[i]->mode == 1)) &&
                 /// Someone else has requested a lock on my LSCA before me.
                 (locks[threadID]->Id == locks[i]->Id
                 || locks[threadID]->criticalAncestors->contains(locks[i]->Id)
                 || locks[i]->criticalAncestors->contains(locks[threadID]->Id)) &&
                 /// It isn't my turn to take the lock
                 (locks[threadID]->Oseq > locks[i]->Oseq));
        });
    }

>>>>>>> blockingImplementation
    bool acquireLock(lockObject * reqObj, int threadID) {
        auto t1 = std::chrono::high_resolution_clock::now();
        lockPoolLock.lock();
        reqObj->Oseq = ++Gseq;
        locks[threadID] = reqObj;
        lockPoolLock.unlock();
        for(int i=0;i< SIZE; i++){
            /// A thread won't run into conflict with itself.
<<<<<<< HEAD
            /// Spin waiting on the condition.
            auto l = locks[i];
            while (l!= nullptr &&
             /// If a read lock is requested for an object that is read locked, only then allow it.
             (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
             /// Someone else has requested a lock on my LSCA before me (locked Sub-Hierarchy)or
             /// I am the LSCA of some node that is locked already (locked Super-hierarchy).
             (l->criticalAncestors.contains(reqObj->Id)) &&
             /// It isn't my turn to take the lock
             (reqObj->Oseq > l->Oseq)) {
                if(processor_Count<parameters.getThreadNum()) this_thread::yield();
                l=locks[i];
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        idleness[threadID] += t2-t1;
=======
            /// A thread won't run into conflict with itself.
            if(locks[i] != nullptr){

                /// Spin waiting on the condition.
                auto l = locks[i];
                if (l!= nullptr &&
                       /// If a read lock is requested for an object that is read locked, only then allow it.
                       (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                       /// Someone else has requested a lock on my LSCA before me.
                       (reqObj->Id == l->Id
                       || reqObj->criticalAncestors->contains(l->Id)
                       || l->criticalAncestors->contains(reqObj->Id)) &&
                       /// It isn't my turn to take the lock
                       (reqObj->Oseq > l->Oseq)) {
//                    if(processor_Count<parameters.getThreadNum()) this_thread::yield();
//                    l=locks[i];
                    l->accessController.wait(true);
                }
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        idleness[threadID] += (t2-t1);
>>>>>>> blockingImplementation
        return true;
    }

    void releaseLock(lockObject *l, int threadId){
<<<<<<< HEAD
        lockPoolLock.lock();
        locks[threadId] = nullptr;
        lockPoolLock.unlock();
=======
//        std::unique_lock<std::shared_mutex> lk (threadMutexes[threadId]);
        locks[threadId] = nullptr;
        l->accessController.clear();
        l->accessController.notify_all();
//        threadConditions[threadId].notify_all();
>>>>>>> blockingImplementation
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
