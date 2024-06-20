#include <pthread.h>
#include <ctime>
#include <sys/time.h>

#include "thread.h"

#define MILLISECONDS_IN_SECOND 1000
#define MICROSECONDS_IN_SECOND 1000000
#define MICROSECONDS_IN_MILLISECOND 1000
#define NANOSECONDS_IN_MILLISECOND 1000000

namespace sb7 {

    static pthread_key_t thread_data_key;

    static void thread_destroy_data_key(void *td);

    void global_thread_init() {
        pthread_key_create(&thread_data_key, thread_destroy_data_key);
    }

    void thread_init() {
        ThreadData *td = new ThreadData();
        pthread_setspecific(thread_data_key, td);
    }

    void init_thread_init() {
        ThreadData *td = new ThreadData();
        pthread_setspecific(thread_data_key, td);
    }

    void thread_destroy_data_key(void *td) {
        ThreadData *threadData = (ThreadData *) td;
        delete threadData;
    }

    void thread_clean() {
        // empty
    }

    ThreadData *get_thread_data() {
        return (ThreadData *) pthread_getspecific(thread_data_key);
    }

    Random *get_random() {
        return get_thread_data()->getRandom();
    }

    bool sleep(int msec) {
        time_t sec = msec / MILLISECONDS_IN_SECOND;
        long nsec = (msec % MILLISECONDS_IN_SECOND) * NANOSECONDS_IN_MILLISECOND;

        struct timespec req;
        req.tv_sec = sec;
        req.tv_nsec = nsec;

        return nanosleep(&req, NULL) != -1;
    }

    long get_time_ms() {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec * MILLISECONDS_IN_SECOND +
               t.tv_usec / MICROSECONDS_IN_MILLISECOND;
    }

    long get_time_us() {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec * MICROSECONDS_IN_SECOND + t.tv_usec;
    }
}
