//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include "vector"
#include "mutex"
#include "thread"
extern int threads;

using namespace std;


class lockObject{
public:
    unordered_set<long int>* criticalAncestors;
    int Id;
    int mode;
    long Oseq;

    lockObject(int pId, unordered_set<long int> * ancestors, long int m){
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
    long int Gseq;
    ///CAnnot initialise here because the pool is created and initialised before the parameters are read from the console.
    //bool blockingAllowed = parameters.threadBlockingAllowed();

    lockPool(){
        //cout<<"Cores available "<<processor_Count<<endl;
        Gseq = 0;
        for(int i=0; i<SIZE;i++)
        {
            locks[i] = nullptr;
        }
    }

    static bool hasCriticalAncestor(unordered_set<long int> * A, int d){
        for(auto a :*A){
            if(a==d) return true;
        }
//        if(A->find(d) !=A->end()){
//            return true;
//        }
        return false;
    }


    bool acquireLock(lockObject * reqObj, int threadID) {
        //cout<<"Threads running "<<threads<<endl;
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
             (reqObj->Id == l->Id ||
             (hasCriticalAncestor(reqObj->criticalAncestors, l->Id)) ||
             (hasCriticalAncestor(l->criticalAncestors, reqObj->Id))) &&
             /// It isn't my turn to take the lock
             (reqObj->Oseq > l->Oseq)) {
                if(threads>processor_Count) this_thread::yield();
                l=locks[i];
            }
        }
        return true;
    }

    void releaseLock(int threadId){
            locks[threadId] = nullptr;
    }

};


#endif //STMBENCH_LOCKPOOL_H
