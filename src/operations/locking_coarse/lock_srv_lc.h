#ifndef SB7_LOCK_SRV_LC_H_
#define SB7_LOCK_SRV_LC_H_

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
			pthread_rwlock_t lock;
	};
}

extern sb7::LCLockSrv lc_lock_srv;

#endif // SB7_LOCK_SRV_LC_H_
