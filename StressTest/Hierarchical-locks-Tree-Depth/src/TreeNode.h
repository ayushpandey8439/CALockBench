#ifndef TREENODE_H
#define TREENODE_H
#include <pthread.h>
#include "list"
#include "unordered_set"
using namespace std;
int nodeId=1;
class TreeNode {
public:
	
	bool IsExplored;
	bool active;
	bool parentUpdated;
	int data;
	pthread_mutex_t Lock;
	pthread_rwlock_t rwlock;
	int IsIx;
	int refCounter;
	int preNumber;
	int postNumber;
	class TreeNode *left;
	class TreeNode *right;
	class TreeNode *parent;
    list<int> pathLabel{};
    unordered_set<int> criticalAncestors;
	TreeNode(int);
};

TreeNode::TreeNode(int key)
{
  int rc = pthread_rwlock_init(&rwlock, NULL);
  
	IsExplored = 0;
	bool active = 0;
	parentUpdated = 0;
	data=key;
  	IsIx=0;
  	refCounter=0;
    //this->pathLabel.push_back(id);
    this->criticalAncestors.insert(key);
}




#endif
