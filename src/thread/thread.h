#ifndef SB7_THREAD_H_
#define SB7_THREAD_H_

/**
 * @file thread.h
 * 
 * This file contains definitions of things that are related to thread
 * management and are not defined in appropriate way in rstm library
 * itself.
 * 
 */

#include <iostream>

#include <pthread.h>

#include "../random.h"

namespace sb7 {

    class ThreadData {
    public:
        Random *getRandom() {
            return &random;
        }

    private:
        // random
        Random random;
    };

    class LockHandle {
    public:
        LockHandle(pthread_rwlock_t *l, int s = 1) : lock(l), size(s) {
        }

        virtual ~LockHandle() {
            for (int i = 0; i < size; i++) {
                pthread_rwlock_unlock(lock + i);
            }
        }

    protected:
        pthread_rwlock_t *lock;
        int size;
    };

    class ReadLockHandle : public LockHandle {
    public:
        ReadLockHandle(pthread_rwlock_t *l, int s = 1) : LockHandle(l, s) {
            for (int i = size - 1; i >= 0; i--) {
                pthread_rwlock_rdlock(lock + i);
            }
        }
    };

    class WriteLockHandle : public LockHandle {
    public:
        WriteLockHandle(pthread_rwlock_t *l, int s = 1) : LockHandle(l, s) {
            for (int i = size - 1; i >= 0; i--) {
                pthread_rwlock_wrlock(lock + i);
            }
        }
    };

    /**
     * Initialize data shared by all threads.
     */
    void global_thread_init();

    /**
     * Initialize specific thread.
     */
    void thread_init();

    /**
     * Special initialization for init thread.
     */
    void init_thread_init();

    /**
     * Clean after the thread.
     */
    void thread_clean();

    /**
     * Get thread local thread data.
     */
    ThreadData *get_thread_data();

    /**
     * Shortcut for getting thread local random object.
     */
    Random *get_random();

    /**
     * Convenience function for delaying thread for time interval
     * that is specified in milliseconds.
     */
    bool sleep(int ms);

    /**
     * Get time in ms since epoch. This function might be architecture specific.
     */
    long get_time_ms();

    /**
     * Get time in us since epoch. This function might be architecture specific.
     */
    long get_time_us();
}

#endif /*SB7_THREAD_H_*/
