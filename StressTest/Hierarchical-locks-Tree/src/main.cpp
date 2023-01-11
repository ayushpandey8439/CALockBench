#include<iostream>
#include"TreeNode.h"
#include"Tree.h"
#include"errorHandler.h"
#include<stdlib.h>
#include<string.h>
#include"ParallelPthread.h"
#include <sys/time.h>
#include"intervalTree.h"
#include "interval.h"
#include "lockPool.h"
//#include<atomic>
using namespace std;
int caseParameter;
int NoOfRequestedNode;
int distribution;
IntervalCheck ICheck;
lockPool pool;
int N;
int threads;
char CSSize;

TreeNode** Array;
int main(int argc, char *argv[])
{	
	srand(12345);
	err *e=new err();
	Tree *T=new Tree();
    ParallelThread *th=new ParallelThread();
	int NoOfNodesDS = atoi(argv[1]);
	int NoOfThreads = atoi(argv[2]);
	caseParameter = atoi(argv[3]);
	NoOfRequestedNode = atoi(argv[4]);
	distribution = atoi(argv[5]);
	CSSize = argv[6][0];
	N=atoi(argv[1]);
    threads = NoOfThreads;
    
	Array = new TreeNode*[N];

	if(e->errCheck(argc, argv))
	{
		T->CreateTree(NoOfNodesDS);//defined in "tree.h"
	}
    
	T->setPathToNode(NoOfNodesDS);//defined in "tree.h"
	
	//cout<<"\nHead data\n"<<T->head->left->data;
	//T->DFS(T->head);
    if(caseParameter==5){
        T->ModifiedDFS(T->head);
    }

    if(caseParameter==7){
        T->CALabelling(T->head);
    }

	//T->preorder(T->head);

	double average=0;
	//cout<<"\nThread creation start";
	//create threads
	for(int i=0;i<5;i++)
	{  
		struct timeval tp;
		gettimeofday(&tp,NULL);
		double start = tp.tv_sec + tp.tv_usec/1000000.0;
    
    
		th->CreateThread(NoOfThreads,T);
    
    
    
		gettimeofday(&tp,NULL);
		double finish = tp.tv_sec + tp.tv_usec/1000000.0;
		double result = finish - start;
		average += result;    
		//cout<<"\n"<<result;
		ITNode *root = NULL;
	}
	
	cout<<average/5<<" ";
	//Print node reference and paths
	// T->printMap();
   
}

