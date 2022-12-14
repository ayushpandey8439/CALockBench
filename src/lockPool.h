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

#define SIZE 32
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
    mutex lockPoolLock;
    lockObject* locks[SIZE];
    mutex threadMutexes[SIZE];
    condition_variable threadConditions[SIZE];
    std::atomic<long int> Gseq;
    ///CAnnot initialise here because the pool is created and initialised before the parameters are read from the console.
    //bool blockingAllowed = parameters.threadBlockingAllowed();

    lockPool(){
        Gseq = 1;
        for(int i=0; i<SIZE;i++)
        {
            locks[i] = nullptr;
        }
    }


    bool acquireLock(lockObject * reqObj, int threadID) {
        //lockPoolLock.lock();
        reqObj->Oseq = Gseq.fetch_add(1);
        locks[threadID] = reqObj;
        //lockPoolLock.unlock();
        //Shortcut to allow readers to take locks. If the number of writers is 0 and only a read lock is requested, then allow the fast track read lock.
        for(int i=0;i< SIZE; i++){
            /// A thread won't run into conflict with itself.
            if(locks[i] != nullptr && i!= threadID){
                if(parameters.threadBlockingAllowed()) {
                    /// Threads are blocked until the condition is true;
                    std::unique_lock<std::mutex> lck(threadMutexes[i]);
                    /// wait only allows treads to progress if the predicate is true.
                    threadConditions[i].wait(lck, [this, i, threadID] {
                        return (locks[i] == nullptr ||
                                /// Read vs Read is not a conflict
                                (locks[threadID]->mode == 0 && locks[i]->mode == 0) ||
                                /// The hierarchies do not overlap
                                (locks[threadID]->Id != locks[i]->Id &&
                                 !lscaHelpers::hasCriticalAncestor(locks[threadID]->criticalAncestors, locks[i]->Id)) ||
                                /// If all else fails, then at least it should be my turn.
                                locks[threadID]->Oseq <= locks[i]->Oseq);
                    });
                } else {
                    /// Spin waiting on the condition.
                    auto * l = locks[i];
                    while (l!= nullptr &&
                     /// If a read lock is requested for an object that is read locked, only then allow it.
                     (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                     /// Someone else has requested a lock on my LSCA before me.
                     (reqObj->Id == l->Id || lscaHelpers::hasCriticalAncestor(reqObj->criticalAncestors, l->Id)) &&
                     /// It isn't my turn to take the lock
                     reqObj->Oseq > l->Oseq) {
                        l=locks[i];
                    }
                }
            }
        }
        return true;
    }

    void releaseLock(lockObject *l, int threadId){
        if(parameters.threadBlockingAllowed()) threadMutexes[threadId].lock();
        locks[threadId] = nullptr;
        delete l;
        if(parameters.threadBlockingAllowed()){
            threadMutexes[threadId].unlock();
            threadConditions[threadId].notify_all();
        }
    }

    list<int> addToLockRequest(DataHolder*dh, list<int>  lockRequest, list<int> label){
        if(lockRequest.empty()){
            return label;
        } else {
            list<int> common;
            set_intersection(lockRequest.begin(), lockRequest.end(), label.begin(),label.end(), back_inserter(common));
            return common;
        }
    }

//    DesignObj * getLockObject(string objectId, sb7::DataHolder * dh){
//        string typeIdentifier = objectId.substr(0,2);
//        string id = objectId.substr(2);
//        if(typeIdentifier == "ca"){
//            sb7::ComplexAssembly * ca = dh->getComplexAssembly(stoi(id));
//            return ca;
//        } else if(typeIdentifier == "ba") {
//            sb7::BaseAssembly * ba = dh->getBaseAssembly(stoi(id));
//            return ba;
//        } else if(typeIdentifier == "cp"){
//            sb7::CompositePart * cp  = dh->getCompositePart(stoi(id));
//            return cp;
//        } else if(typeIdentifier == "ap"){
//            sb7::Map<int, sb7::AtomicPart *> * index  = dh->getAtomicPartIdIndex();
//            sb7::Map<int, sb7::AtomicPart *>::Query query;
//            query.key = stoi(id);
//            index->get(query);
//            return query.val;
//        } else {
//            return NULL;
//        }
//    }
};


#endif //STMBENCH_LOCKPOOL_H
