

#ifndef SB7_INTERVAL_H_
#define SB7_INTERVAL_H_

#include <vector>
#include <stdlib.h>
using namespace std;
#define SIZE 20
class interval{

public: long int pre, post, mode;
    long MySeq;
	interval( long int a, long int b, long int m){
	pre = a; post = b; mode = m;
	}
};

//**************************************************************************************************************
class IntervalCheck{
public:
    long Seq;
interval *Array[SIZE];
pthread_rwlock_t ArrayLock[SIZE];
pthread_mutex_t mutex;
IntervalCheck()
{
	for(long int i = 0;i<SIZE; i++)
	{
		
		Array[i] = NULL;
		pthread_rwlock_t ArrayLock[i];
	}



}

bool IsOverlap(interval *inv, long int m, long int threadID)
{
    //cout<<"m=1";
    pthread_mutex_lock(&mutex);
    inv->MySeq = ++Seq;
    Array[threadID] = inv;
    pthread_mutex_unlock(&mutex);

    for(long int i=0; i< SIZE; i++)
    {
        if(Array[i] != nullptr)
        {
            interval *ptr = Array[i];
            //wait untill there is an overlap and my sequence number is greater
            while(ptr !=NULL &&
                  (inv->mode==1 || (inv->mode == 0 && ptr->mode == 1)) &&
                  ((ptr->pre <= inv->post && ptr->post>= inv->post) || (ptr->post >= inv->pre && ptr->pre<=inv->pre))
                  && ptr->MySeq < inv->MySeq)
            {
                ptr = Array[i];
            }
        }
    }

    return false;
}


//void Insert(interval *inv, long int index)
//{
//
//	//pthread_rwlock_wrlock(&ArrayLock[index]);
//	Array[index] = inv;
//	//pthread_rwlock_unlock(&ArrayLock[index]);
//
//}

void Delete(long int index)
{//index=0;
    pthread_mutex_lock(&mutex);
	Array[index] = NULL;
    pthread_mutex_unlock(&mutex);


}

};

#endif
