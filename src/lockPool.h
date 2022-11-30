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
    int mode;
    long Oseq;
    lockObject(DesignObj * d, int m){
        designObj = d;
        mode = m;
        Oseq=-1;
    }
};

class lockPool {
public:
    int writers;
    mutex lockPoolLock;
    lockObject* locks[SIZE];

    long Gseq;

    lockPool(){
        Gseq = 0;
        writers=0;
        for(auto & lock : locks)
        {
            lock = nullptr;
        }
    }


    bool acquireLock(lockObject * reqObj, int threadID){
        // A thread can only be one of two places. It can either be taking a lock or releasing one. So, the threadId index ensures that an element in the array is not concurrently modified.
        //lockPoolLock.lock();
        reqObj->Oseq = ++Gseq;
        locks[threadID] = reqObj;
        //lockPoolLock.unlock();
        //Shortcut to allow readers to take locks. If the number of writers is 0 and only a read lock is requested, then allow the fast track read lock.
        for(int i=0;i< SIZE; i++){
            if(locks[i] != nullptr){
                lockObject * l = locks[i];
                while(l!= nullptr &&
                        // If a read lock is requested for an object that is read locked, only then allow it.
                        (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                        // Someone else has requested a lock on my LSCA before me.
                        //std::any_of(locks[0], locks[SIZE-1], [&reqObj, &lsca](lockObject o){return (o.designObj==lsca && o.Oseq < reqObj->Oseq);})
                        reqObj->designObj->hasCriticalAncestor(l->designObj) &&
                        //lockedLSCA(locks, lscaHelpers::findLSCA(l->designObj->getPathLabel(),reqObj->designObj->getPathLabel()) , reqObj->Oseq)

                        // It isn't my turn to take the lock
                        reqObj->Oseq > l->Oseq
                    ){
                    //cout<<"waiting for lock resolution on "<< this_thread::get_id()<<endl;
                        l=locks[i];
                    }
            }
        }
        if(reqObj->mode==1){
            writers++;
        }
        return true;
    }


    static bool lockedLSCA(lockObject * lockedObjs[SIZE], DesignObj* lsca, long seqNo){
        for(int i=0; i<SIZE; i++){
            if(lockedObjs[i] != nullptr){
                auto * l = lockedObjs[i];
                if(l != nullptr && l->designObj == lsca && l->Oseq< seqNo){
                    return true;
                }
            }
        }
        return false;
    }

    void releaseLock(lockObject* l, int threadId){
        if(l->mode==1){
            writers--;
        }
        locks[threadId] = nullptr;
    }

    DesignObj* addToLockRequest(DesignObj*  lockRequest, DesignObj* label){
        if(lockRequest== nullptr){
            return label;
        } else {
            return lscaHelpers::findLSCA(lockRequest, label);
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
