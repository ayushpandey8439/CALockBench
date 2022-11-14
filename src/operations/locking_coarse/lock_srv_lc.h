//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_LOCK_SRV_LC_H
#define STMBENCH_LOCK_SRV_LC_H


#include <pthread.h>

namespace sb7 {

    class LCLockSrv {
    public:
        LCLockSrv() {
            initializeLock();
        }

        ~LCLockSrv() {
            destroyLock();
        }

        pthread_rwlock_t *getLock() {
            return &lock;
        }

    protected:
        void initializeLock();

        void destroyLock();

    protected:
        pthread_rwlock_t lock{};
    };
}

extern sb7::LCLockSrv lc_lock_srv;


#endif //STMBENCH_LOCK_SRV_LC_H
