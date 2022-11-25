//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include <vector>
#include <set>
#include <string>
#include <thread>         // std::thread
#include <shared_mutex>
#include "data_holder.h"
#include "lscaHelpers.h"
#include "iostream"

#define SIZE 32
using namespace std;
using namespace sb7;


struct classcomp {
    bool operator() (const DesignObj* lhs, const DesignObj* rhs) const
    {return lhs->getId()<rhs->getId();}
};

class lockObject{
public:
    DesignObj* designObj;
    char mode;
    long Oseq;
    lockObject(DesignObj* d, char m){
        designObj = d;
        mode = m;
    }
};

class lockPool {
public:
    mutex lockPoolLock;
    lockObject* locks[SIZE];
    //Lock variable, one per lock-pool location
    pthread_rwlock_t ArrayLock[SIZE];

    long Gseq;
    //Sequence number per thread for fairness and less contention
    long Seq[SIZE];

    lockPool(){
        Gseq = 0;
        for(int i = 0;i<SIZE; i++)
        {
            locks[i] = NULL;
            pthread_rwlock_t ArrayLock[i];
        }
    }


    bool acquireLock(lockObject * reqObj, int threadID){
        lockPoolLock.lock();
        reqObj->Oseq = ++Gseq;
        locks[threadID] = reqObj;
        lockPoolLock.unlock();

        for(int i=0;i< SIZE; i++){
            lockObject * lockedObj = locks[i];
            if(lockedObj != NULL){
                vector<DesignObj*> lockedLabel = lockedObj->designObj->getPathLabel();
                DesignObj* common = lscaHelpers::findLSCA(lockedLabel,reqObj->designObj->getPathLabel());
                while(lockedObj!= NULL &&
                // If a read lock is requested for an object that ia read locked, then allow it. Otherwise, don't.
                (reqObj->mode =='r' && lockedObj->mode == 'w') &&
                (
                // It isn't my turn to take the lock
                reqObj->Oseq > lockedObj->Oseq ||
                // I'm already locked
                reqObj == lockedObj ||
                // Someone else has requested a lock on my LSCA before me.
                std::any_of(locks[0], locks[SIZE-1], [&reqObj, &common](lockObject o){return (o.designObj==common && o.Oseq < reqObj->Oseq);})
                )){
                    cout<<"waiting for lock resolution on "<< this_thread::get_id()<<endl;
                    this_thread::sleep_for(chrono::milliseconds(1));
                }
            }
        }
        return true;
    }

    void releaseLock(int threadId){
        locks[threadId] = NULL;
    }

    vector<DesignObj*> addToLockRequest(vector<DesignObj*> lockRequest, vector<DesignObj*> label){
        if(lockRequest.empty()){
            return label;
        } else {
            return lscaHelpers::findLSCA(lockRequest, label)->getPathLabel();
        }
    }

    DesignObj * getLockObject(string objectId, sb7::DataHolder * dh){
        string typeIdentifier = objectId.substr(0,2);
        string id = objectId.substr(2);
        if(typeIdentifier == "ca"){
            sb7::ComplexAssembly * ca = dh->getComplexAssembly(stoi(id));
            return ca;
        } else if(typeIdentifier == "ba") {
            sb7::BaseAssembly * ba = dh->getBaseAssembly(stoi(id));
            return ba;
        } else if(typeIdentifier == "cp"){
            sb7::CompositePart * cp  = dh->getCompositePart(stoi(id));
            return cp;
        } else if(typeIdentifier == "ap"){
            sb7::Map<int, sb7::AtomicPart *> * index  = dh->getAtomicPartIdIndex();
            sb7::Map<int, sb7::AtomicPart *>::Query query;
            query.key = stoi(id);
            index->get(query);
            return query.val;
        } else {
            return NULL;
        }
    }
};


#endif //STMBENCH_LOCKPOOL_H
