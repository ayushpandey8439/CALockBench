#include "lock_srv_lm.h"

void sb7::LMLockSrv::initializeLocks() {
    ::pthread_rwlock_init(&structureModificationLock, nullptr);

    // initialize assembly level locks
    for (int i = 0; i < MAX_ASSEMBLY_LOCKS; i++) {
        ::pthread_rwlock_init(assemblyLockArray + i, nullptr);
    }

    ::pthread_rwlock_init(&compositePartLock, nullptr);
    ::pthread_rwlock_init(&atomicPartLock, nullptr);
    ::pthread_rwlock_init(&documentLock, nullptr);
    ::pthread_rwlock_init(&manualLock, nullptr);
}

void sb7::LMLockSrv::destroyLocks() {
    ::pthread_rwlock_destroy(&structureModificationLock);

    // free assembly level locks
    for (int i = 0; i < MAX_ASSEMBLY_LOCKS; i++) {
        ::pthread_rwlock_destroy(assemblyLockArray + i);
    }

    ::pthread_rwlock_destroy(&compositePartLock);
    ::pthread_rwlock_destroy(&atomicPartLock);
    ::pthread_rwlock_destroy(&documentLock);
    ::pthread_rwlock_destroy(&manualLock);
}

// define the static lock server variable
sb7::LMLockSrv lm_lock_srv;
