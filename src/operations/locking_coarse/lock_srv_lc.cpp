#include "lock_srv_lc.h"

void sb7::LCLockSrv::initializeLock() {
    ::pthread_rwlock_init(&lock, nullptr);
}

void sb7::LCLockSrv::destroyLock() {
    ::pthread_rwlock_destroy(&lock);
}

sb7::LCLockSrv lc_lock_srv;
