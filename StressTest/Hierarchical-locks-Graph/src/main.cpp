#include<iostream>
#include"TreeNode.h"
#include"Tree.h"
#include"errorHandler.h"
#include<stdlib.h>
#include"ParallelPthread.h"
#include <sys/time.h>
#include"intervalTree.h"
#include "interval.h"
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
	srand(12345);//Use a fixed random seed to ensure result replication across all the runs.
	//srand(0);	
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

	Array = new TreeNode*[N+1];
//cout<<"Data Structure creation started \n";
	if(e->errCheck(argc, argv))
	{
		T->CreateGraph(50);//defined in "tree.h"
	}
  //cout<<"Data Structure creation finished \n";  
	//T->setPathToNode(NoOfNodesDS);//defined in "tree.h"
	
	//cout<<"\nHead data\n"<<T->head->left->data;
	//T->DFS(T->head);
    
//cout<<"Numbering Algorithm started \n";
if(caseParameter==5){
    T->ModifiedDFS(T->head);
}

if(caseParameter==7){
    T->CALabelling(T->head);
}

//cout<<"numbering algo finished \n";

    //T->preorder(T->head);
	//std::vector<int>V;
	
	//T->findAllParents(Array[1], V);
	//cout<<"here we go"<<V.size();	
	double average=0;
	//cout<<"\nThread creation start";
	//create threads
	for(int i=0;i<5;i++)
	{  
		struct timeval tp;
		gettimeofday(&tp,NULL);
		double start = tp.tv_sec + tp.tv_usec/1000000.0;
    
    
		th->CreateThread(NoOfThreads,T);//defined in "parallelPthread.h"
    
    
    
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

