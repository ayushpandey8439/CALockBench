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
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

	srand(1111);
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
		TreeNode* h = T->CreateTree(1,NoOfNodesDS);//defined in "tree.h"
        T->head = h;
        std::sort(T->LeafNodes.begin(), T->LeafNodes.end());
	}
    //T->preorder(T->head);
	T->setPathToNode(T->head, "");//defined in "tree.h"
	
	//cout<<"\nHead data\n"<<T->head->left->data;
	//T->DFS(T->head);
    if(caseParameter==5){
        T->ModifiedDFS(T->head);
    }

    if(caseParameter==7){
        T->CALabelling(T->head);
    }

	//cout<<"\nThread creation start";
	//create threads

    auto t1 = high_resolution_clock::now();
    
    
	th->CreateThread(NoOfThreads,T);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
		//cout<<"\n"<<result;
		ITNode *root = NULL;
	cout<<ms_double.count()<<" ";
	//Print node reference and paths
	// T->printMap();
   
}

