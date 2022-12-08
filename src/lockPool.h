//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include <set>
#include <string>
#include <thread>         // std::thread
#include <shared_mutex>
#include "data_holder.h"
#include "lscaHelpers.h"
#include "iostream"
#include "parameters.h"
#include <algorithm>

#define SIZE 32
using namespace std;
using namespace sb7;

class lockObject{
public:
    unordered_set<string> criticalAncestors;
    string Id;
    int mode;
    long Oseq;

    lockObject(const DesignObj d, int m){
        Id = d.getStringId();
        criticalAncestors = d.criticalAncestors;
        mode = m;
        Oseq=-1;
    }
};

class lockPool {
public:
    mutex lockPoolLock;
    lockObject* locks[SIZE];
    pthread_mutex_t threadMutexes[SIZE];
    pthread_cond_t threadConditions[SIZE];
    long Gseq;

    lockPool(){
        Gseq = 0;
        for(int i=0; i<SIZE;i++)
        {
            locks[i] = nullptr;
            threadMutexes[i] = PTHREAD_MUTEX_INITIALIZER;
            threadConditions[i] = PTHREAD_COND_INITIALIZER;
        }
    }


    bool acquireLock(lockObject * reqObj, int threadID) {
        lockPoolLock.lock();
        reqObj->Oseq = ++Gseq;
        locks[threadID] = reqObj;
        lockPoolLock.unlock();
        //Shortcut to allow readers to take locks. If the number of writers is 0 and only a read lock is requested, then allow the fast track read lock.
        for(int i=0;i< SIZE; i++){
            if(locks[i] != nullptr){
                pthread_mutex_lock(&threadMutexes[i]);
                lockObject * l = locks[i];
                while(l!= nullptr &&
                        // If a read lock is requested for an object that is read locked, only then allow it.
                        (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                        // Someone else has requested a lock on my LSCA before me.
                        (reqObj->Id == l->Id || lscaHelpers::hasCriticalAncestor(reqObj->criticalAncestors, l->Id)) &&
                        // It isn't my turn to take the lock
                        reqObj->Oseq > l->Oseq
                    ){
                        //cout<<reqObj->Oseq<<endl;
                        //pthread_cond_broadcast(&threadConditions[i]);

                        int waitStatus = pthread_cond_wait(&threadConditions[i], &threadMutexes[i]);
                        //cout<<waitStatus<<" On " <<threadID<<endl;
                        l=locks[i];
                    }
                pthread_mutex_unlock(&threadMutexes[i]);
            }
        }
        return true;
    }

    void releaseLock(lockObject* l, int threadId){
        pthread_mutex_lock(&threadMutexes[threadId]);
        locks[threadId] = nullptr;
        pthread_mutex_unlock(&threadMutexes[threadId]);
        pthread_cond_broadcast(&threadConditions[threadId]);


    }

    list<string> addToLockRequest(DataHolder*dh, list<string>  lockRequest, list<string> label){
        if(lockRequest.empty()){
            return label;
        } else {
            list<string> common;
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
