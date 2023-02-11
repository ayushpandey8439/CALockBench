//
// Created by Ayush Pandey on 11/02/2023.
//

#ifndef SB7_LOCK_MEDIUMPOOL_H
#define SB7_LOCK_MEDIUMPOOL_H
#include "mutex"
#include "parameters.h"
#include "thread"
using namespace sb7;
using namespace std;
class mediumLock{
public:
    int mode;
    long Oseq;
    int type;

    mediumLock(int m, int t){
        mode = m;
        Oseq=-1;
        type = t;
    }
};

class mediumPool{
    mediumLock* locks[256];
    mutex lockPoolLock;
    const uint32_t processor_Count = std::thread::hardware_concurrency();
public:
    long int Gseq;
    mediumPool(){
        Gseq = 0;
        for(auto & lock : locks)
        {
            lock = nullptr;
        }
    }


    bool acquire(mediumLock *reqObj, int threadId){
        lockPoolLock.lock();
        reqObj->Oseq = Gseq++;
        locks[threadId] = reqObj;
        lockPoolLock.unlock();
        for(int i=0;i< 256; i++){
            /// A thread won't run into conflict with itself.
            /// A thread won't run into conflict with itself.
            if(locks[i] != nullptr){
                /// Spin waiting on the condition.
                auto l = locks[i];
                while (l!= nullptr &&
                       /// If a read lock is requested for an object that is read locked, only then allow it.
                       (reqObj->mode == 1 || (reqObj->mode==0 && l->mode == 1)) &&
                       (reqObj->type == l->type || l->type==0) &&
                       /// It isn't my turn to take the lock
                       (reqObj->Oseq > l->Oseq)) {
                    if(processor_Count<parameters.getThreadNum()) this_thread::yield();
                    l=locks[i];
                }
            }
        }
        return true;
    }
    void release(int threadId){
        locks[threadId] = nullptr;
    }
};
#endif //SB7_LOCK_MEDIUMPOOL_H
