//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include "vector"
#include "mutex"
#include "thread"

using namespace std;


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
        for(int i=0;i< SIZE; i++){
            /// Spin waiting on the condition.
            auto l = locks[i];
            while (l!= nullptr &&
             /// If a read lock is requested for an object that is read locked, only then allow it.
             (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
             /// Someone else has requested a lock on my LSCA before me.
             (reqObj->Id == l->Id || (reqObj->criticalAncestors->find(l->Id) != reqObj->criticalAncestors->end())) &&
             /// It isn't my turn to take the lock
             (reqObj->Oseq > l->Oseq)) {
                this_thread::yield();
                l=locks[i];
            }
        }
        return true;
    }

    void releaseLock(int threadId){
            locks[threadId] = nullptr;
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