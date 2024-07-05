//
// Created by Ayush Pandey on 04/07/2024.
//

#ifndef FLEXIPOOL_H
#define FLEXIPOOL_H

using namespace std;
#define NUM_THREADS 256
#define NUM_BITS 10000000
#define READ_MODE 0
#define WRITE_MODE 1
#define FINE_GRAINED 0
#define HIERARCHICAL 1
#define NOT_LOCKED 2

using namespace sb7;
/*Note: A single instance of this class is used in the application. It is created in sb7_lock.cc */
class FlexiPool
{
public:
    vector<bitset<NUM_BITS>> lockState; // lockState[tid] holds the bit vector with locked indices = 1.
    vector<int> lockMode; // 0 => read, 1 => write, 2 => NotLocked
    vector<int> lockGranularity; // 0 => Fine-grained, 1 => Hierarchical, 2 => NotLocked
    vector<int> levelLocked;
    pthread_mutex_t mutex;
    long globalSequenceNumber;
    int seqNumArray[NUM_THREADS];
    std::chrono::duration<long double, std::nano> idleness[NUM_THREADS];
    std::chrono::duration<long double, std::nano> modificationTime;
    atomic<long int> count = 1;

    FlexiPool()
    {
        globalSequenceNumber = 0;
        int ret = pthread_mutex_init(&mutex, NULL);
        if (ret != 0)
        {
            cout << "Some problem with initializing the mutex lock" << endl;
        }
        lockState.reserve(NUM_THREADS);
        lockState.resize(NUM_THREADS);
        lockMode.reserve(NUM_THREADS);
        lockMode.resize(NUM_THREADS);
        lockGranularity.reserve(NUM_THREADS);
        lockGranularity.resize(NUM_THREADS);
        levelLocked.reserve(NUM_THREADS);
        levelLocked.resize(NUM_THREADS);

        for (int i = 0; i < NUM_THREADS; i++)
        {
            lockState[i].reset();
        }

        cout << "\nLockPool Constructed..." << endl;
    }

    int hash(int x)
    {
        return x; // Place the appropriate linear hash function here.
    }

    bool isLockedNodeAncestor(int requestor_tid, int from, int to, int alreadyLockedBy_tid)
    {
        if ((lockState[requestor_tid] ^ lockState[alreadyLockedBy_tid]).none())
        {
            if (levelLocked[alreadyLockedBy_tid] <= levelLocked[requestor_tid]) // Note: Level of root is 0
                return true; // Both the nodes involved are the same or the already locked one is an ancestor
        }
        // Checking if ancestor
        bitset<NUM_BITS> temp = lockState[requestor_tid] | lockState[alreadyLockedBy_tid];
        bool a, b;
        a = false, b = false;
        int c = NUM_BITS - 1;
        for (int i = 0; i <= from; i++)
        {
            if (temp.test(i))
            {
                a = true;
                break;
            }
        }

        for (int i = to; i <= c; i++)
        {
            if (temp.test(i))
            {
                b = true;
                break;
            }
        }
        return (a && b);
    }

    bool isLockedNodeDescendant(int requestor_tid, int from, int to, int alreadyLockedBy_tid)
    {
        if ((lockState[requestor_tid] ^ lockState[alreadyLockedBy_tid]).none())
        {
            if (levelLocked[alreadyLockedBy_tid] >= levelLocked[requestor_tid]) // Note: Level of root is 0
                return true; // Both the nodes involved are the same or the already locked one is a descendant
        }
        // Checking if descendant
        bitset<NUM_BITS> temp = lockState[requestor_tid] | lockState[alreadyLockedBy_tid];
        bool a, b;
        a = false, b = false;
        int iMax = from - 1;
        for (int i = 0; i <= iMax; i++)
        {
            if (temp.test(i))
            {
                a = true; // 1 present before index from
                break;
            }
        }
        int iMin = to + 1;
        iMax = NUM_BITS - 1;
        for (int i = iMin; i <= iMax; i++)
        {
            if (temp.test(i))
            {
                b = true; // 1 present after index to.
                break;
            }
        }
        // For the node already locked to be a descendant of the newly requested node, temp should not have any bit set in both the ranges [0, from -1] and [to + 1, NUM_BITS - 1]
        return (!a && !b);
    }


    bool doOverlap(int from, int to, int mode, int requestor_tid, int granularity, int levelOfNode, int from2, int to2)
    // Think of read/write modes...
    {
        //					printf("Entered doOverlap for tid = %d, (%d, %d)\n\n", requestor_tid, from, to);
        if (parameters.getThreadNum() > 1)
        {
            int i = hash(from);
            int j = hash(to);
            int mySeq;
            pthread_mutex_lock(&mutex);
            mySeq = ++globalSequenceNumber;
            pthread_mutex_unlock(&mutex);
            seqNumArray[requestor_tid] = mySeq;
            lockRange(i, j, mode, requestor_tid, granularity, levelOfNode, from2, to2);
            //					lockRange(from, to, mode, requestor_tid, granularity, levelOfNode);


            for (int threadNum = 0; threadNum < parameters.getThreadNum(); threadNum++)
            {
                if (threadNum != requestor_tid)
                {
                    while (doRangesOverlap(requestor_tid, threadNum, mode, from, to) && seqNumArray[threadNum] < mySeq)
                    {
                        // Wait in the loop
                    }
                }
            }
        }
        return false;
        // This fn always returns no overlap, as the thread waits until its job is done and then only returns.
    }

    bool doRangesOverlap(const int my_tid, const int tid_in_pool, const int mode, const int from, const int to)
    {
        if ((mode == WRITE_MODE || lockMode[tid_in_pool] == WRITE_MODE) && ((lockState[my_tid] & lockState[tid_in_pool])
            .any()))
        {
            if ((lockGranularity[my_tid] == HIERARCHICAL) && (lockGranularity[tid_in_pool] == HIERARCHICAL))
            {
                // Both are hierarchical type
                return true;
            }
            if (lockGranularity[my_tid] == FINE_GRAINED)
            // my_tid requests for a fine-grained lock, check if the already locked one is hierarchical
            {
                if (lockGranularity[tid_in_pool] == FINE_GRAINED)
                {
                    if (((lockState[my_tid] ^ lockState[tid_in_pool]).none()) &&
                        (levelLocked[my_tid] == levelLocked[tid_in_pool]))
                        return true; //The conflict is with fine-grained lock, and the nodes involved are the same.
                    else
                        return false;
                    // There is no actual conflict -- just that the nodes are ancestor-descendants with the same interval values.
                }
                else if (isLockedNodeAncestor(my_tid, from, to, tid_in_pool))
                    return true;
                // The conflicting node is either the requested node itself or an ancestor. Also it is locked in hierarchical mode
            }
            else // my_tid requests for a hierarchical lock, the already locked one is fine-grained
            {
                // The other one is sure to be fine-grained, as the case of both being hierarchical is already handled
                if (isLockedNodeDescendant(my_tid, from, to, tid_in_pool))
                    return true;
                // The lock is held on the requested node itself or on a descendant of it. Hence it is an overlap, reject the new request.
            }
        }
        return false;
    }

    void lockRange(int from, int to, int mode, int tid, int granularity, int levelOfNode, int from2, int to2)
    {
        if (mode == 1)
            lockMode[tid] = WRITE_MODE;
        else
            lockMode[tid] = READ_MODE;
        if (granularity == 1)
            lockGranularity[tid] = HIERARCHICAL;
        else
            lockGranularity[tid] = FINE_GRAINED;
        levelLocked[tid] = levelOfNode;
        int i;
        for (i = from; i <= to; i++)
        {
            lockState[tid].set(i, 1);
        }
        if (to2 > 0)
        {
            // There is a second interval to be locked as part of an edge addition.
            if (from2 >= from && to2 <= to)
            {
                return; // The second range is already locked.
            }
            int iMax = to2;
            if (from2 < from || from2 > to)
            {
                i = from2;
            }
            if (to2 < from || to2 > to)
            {
                iMax = to2;
            }
            else
                iMax = from - 1;
            for (; i <= iMax; i++)
            {
                lockState[tid].set(i, 1);
            }
        }
    }

    void unlockRange(int tid)
    {
        lockState[tid].reset();
        lockMode[tid] = NOT_LOCKED;
        lockGranularity[tid] = NOT_LOCKED;
        levelLocked[tid] = -1;
        //printf("Range %d, %d unlocked by thread %d\n\n", vStart, vEnd, tid);
        seqNumArray[tid] = INT_MAX;
    }
};
#endif //FLEXIPOOL_H
