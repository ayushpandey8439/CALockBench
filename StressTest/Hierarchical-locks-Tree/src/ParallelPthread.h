#ifndef ParallelPthread_H
#define ParallelPthread_H
#include <pthread.h>
extern bool modifications;

using namespace std;
class threadData
{
	public:
	Tree * TreePtr;
	int nodeId;
	int threadID;
  
};
threadData *TD = new threadData();

class ParallelThread
{
	public:
	pthread_mutex_t rootLock;
	int TCS;//checks whether thread created successfully


    ParallelThread();
	void coarseLock();
	void coarseUnLock();
	void CreateThread(int,Tree *);
	static void* ParallelTask(void *TD)
	{
		threadData *data = (threadData *)TD;
		Tree *p = data->TreePtr;
		int threadID = data->threadID;
		for(int i=0;i<1000;i++)
		{
			p->DummyTask(threadID);
		}
        return nullptr;
	}
  
};


ParallelThread::ParallelThread()
{
  rootLock= PTHREAD_MUTEX_INITIALIZER;
}




void ParallelThread::CreateThread(int NUM_THREADS,Tree *ptr)
{
  threadData *TD[NUM_THREADS];
 
pthread_t threadArray[NUM_THREADS];

  for(int i=0; i < NUM_THREADS; i++ )
   {
      rand();
	TD[i] = new threadData();
	TD[i]->TreePtr = ptr;
	TD[i]->nodeId = 0;
	TD[i]->threadID = i;
      TCS = pthread_create(&threadArray[i], NULL,&ParallelThread::ParallelTask,(void *)TD[i]);
      if (TCS!=0){
         cout << "Error:unable to create thread," << TCS << endl;
         exit(-1);
      }
   }
   
   //cout<<"WAIT \n";
   for(int i=0;i<NUM_THREADS;i++)
	pthread_join( threadArray[i], NULL );

}



void ParallelThread::coarseLock()
{
pthread_mutex_lock(&rootLock);
}


void ParallelThread::coarseUnLock()
{
pthread_mutex_unlock(&rootLock);
}

#endif







