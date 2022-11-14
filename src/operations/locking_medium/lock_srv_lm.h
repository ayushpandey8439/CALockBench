//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_LOCK_SRV_LM_H
#define STMBENCH_LOCK_SRV_LM_H


#include <pthread.h>

#include "../../parameters.h"

#define MAX_ASSEMBLY_LOCKS 10

namespace sb7 {

    class LMLockSrv {

    public:
        LMLockSrv() {
            initializeLocks();
        }

        ~LMLockSrv() {
            destroyLocks();
        }

        pthread_rwlock_t *getStructureModificationLock() {
            return &structureModificationLock;
        }

        pthread_rwlock_t *getAssemblyLock(int i) {
            return assemblyLockArray + i;
        }

        pthread_rwlock_t *getAssemblyLockArray() {
            return assemblyLockArray;
        }

        pthread_rwlock_t *getBaseAssemblyLock() {
            return assemblyLockArray;
        }

        static int getAssemblyLockArraySize() {
            return parameters.getNumAssmLevels();
        }

        pthread_rwlock_t *getCompositePartLock() {
            return &compositePartLock;
        }

        pthread_rwlock_t *getAtomicPartLock() {
            return &atomicPartLock;
        }

        pthread_rwlock_t *getDocumentLock() {
            return &documentLock;
        }

        pthread_rwlock_t *getManualLock() {
            return &manualLock;
        }

    protected:
        void initializeLocks();

        void destroyLocks();

    protected:
        pthread_rwlock_t structureModificationLock{};
        pthread_rwlock_t compositePartLock{};
        pthread_rwlock_t atomicPartLock{};
        pthread_rwlock_t documentLock{};
        pthread_rwlock_t manualLock{};
        pthread_rwlock_t assemblyLockArray[MAX_ASSEMBLY_LOCKS]{};
    };
}

extern sb7::LMLockSrv lm_lock_srv;


#endif //STMBENCH_LOCK_SRV_LM_H
