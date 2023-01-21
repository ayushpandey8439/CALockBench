#ifndef TREENODE_H
#define TREENODE_H
#include <pthread.h>
#include "list"
#include "unordered_set"
using namespace std;
long int nodeId=1;
class TreeNode {
public:

	bool IsExplored;
	bool active;
	bool parentUpdated;
	long int data;
	pthread_mutex_t Lock;
	pthread_rwlock_t rwlock;
	long int IsIx;
	long int refCounter;
	long long int preNumber;
	long long int postNumber;
	class TreeNode *left;
	class TreeNode *right;
	class TreeNode *parent;
    list<long int> pathLabel{};
    unordered_set<long int> criticalAncestors;
	TreeNode(long int);
    bool operator< (const TreeNode &other) const {
        return data < other.data;
    }
};

TreeNode::TreeNode(long int key)
{
  long int rc = pthread_rwlock_init(&rwlock, NULL);
  
	IsExplored = 0;
	bool active = 0;
	parentUpdated = 0;
	data=key;
  	IsIx=0;
  	refCounter=0;
    //this->pathLabel.push_back(key);
    this->criticalAncestors.insert(key);
}




#endif
