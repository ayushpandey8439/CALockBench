#include "lock_srv_lm.h"

void sb7::LMLockSrv::initializeLocks() {	
	::pthread_rwlock_init(&structureModificationLock, NULL);

	// initialize assembly level locks
	for(int i = 0;i < MAX_ASSEMBLY_LOCKS;i++) {
		::pthread_rwlock_init(assemblyLockArray + i, NULL);
	}

	::pthread_rwlock_init(&compositePartLock, NULL);
	::pthread_rwlock_init(&atomicPartLock, NULL);
	::pthread_rwlock_init(&documentLock, NULL);
	::pthread_rwlock_init(&manualLock, NULL);
}

void sb7::LMLockSrv::destroyLocks() {
	::pthread_rwlock_destroy(&structureModificationLock);

	// free assembly level locks
	for(int i = 0;i < MAX_ASSEMBLY_LOCKS;i++) {
		::pthread_rwlock_destroy(assemblyLockArray + i);
	}

	::pthread_rwlock_destroy(&compositePartLock);
	::pthread_rwlock_destroy(&atomicPartLock);
	::pthread_rwlock_destroy(&documentLock);
	::pthread_rwlock_destroy(&manualLock);
}

// define the static lock server variable
sb7::LMLockSrv lm_lock_srv;
