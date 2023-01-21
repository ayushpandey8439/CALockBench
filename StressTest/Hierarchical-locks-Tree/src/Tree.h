#include"TreeNode.h"
#include<map>
#include<vector>
#include <pthread.h>
#include<algorithm>
#include<unistd.h>//For usleep()
#include <set>
#include"lock.h"
#include "interval.h"
#include "lockPool.h"
#include "random"
using namespace std;


extern IntervalCheck ICheck;
extern lockPool pool;
extern TreeNode** Array;
extern char CSSize;
TreeNode * NodeArray;
class Tree
{
	public:
	pthread_mutex_t rootLock;
	int size;
	TreeNode *head,*nextNode;
	int counter;//dfs counting
	vector<TreeNode *> NodeVector;
	map<long int,TreeNode *> NodeRef;  //map of <key,address> for each tree node.
    vector<TreeNode *> LeafNodes;  //map of <key,address> for each tree node.
	map<long int,string> PathRef;  //Path to  a nade.
  
  
	//Member functions************
	//Constructor
	Tree();
  
	//Preorder traversal
	void preorder(TreeNode *);

	//Insert new node into tree
	void insert(TreeNode *ptr);
  
	//Set pointer to a for next insertion operation
	void setNextNode();
  
	//Save direct address of each Node
	void setNodeRef(TreeNode *ptr);
  
	//Save path from head to node
	void setPathToNode(TreeNode* n, string currpath);
  
	//Print reference map
	void printMap();
  
	//Print path map
	void printPath();
  
	//Create Tree
	TreeNode* CreateTree(long int start, long int end);

	//Concurrent function
	void DummyTask(int node);
    void structuralModification(int tid);
    void relabelDom(TreeNode* node);
	//Depth first search
	void DFS(TreeNode *ptr);

	//Updated parent intervals according to intervals of child nodes
	bool UpdateParent(TreeNode *parent, TreeNode *ptr);

	//New interval numbering algorithm
	void ModifiedDFS(TreeNode *ptr);


	

	void NullOperation()
	{
		int itr;
		if(CSSize == 's')
			itr = 1000;
		else if(CSSize == 'm')
			itr = 10000;
		else if(CSSize == 'l')
			itr = 100000;
		
		for(int i=0;i<itr;i++)
		{		
			int x = 5,y;
			y = x;
		}
	}


    void CALabelling(TreeNode *ptr);
};//end of class "Tree"





//constructor
Tree::Tree()
{
	head = NULL;
	nextNode = NULL;
	counter = 0;
  	size = 0;
}


//This function creates Tree with number of nodes as parameter
TreeNode* Tree::CreateTree(long int start, long int end)
{
    if(start>end)
        return nullptr;

    long int mid = (long int)(start+end)/2;
    auto *newNode=new TreeNode(mid);
    Array[newNode->data]=newNode;
    if(start==end){
        size++;
        LeafNodes.push_back(newNode);
    }
    setNodeRef(newNode);
    newNode->left = CreateTree(start, mid-1);
    if(newNode->left!=nullptr) newNode->left->parent = newNode;
    newNode->right = CreateTree(mid+1, end);
    if(newNode->right!=nullptr) newNode->right->parent = newNode;

    return newNode;
}

//This function saves path from root to perticular node: l=letf pointer r=right pointer
//stores path in string e.g. node 5=lr i.e "root->right->left" starts from end of string.
void Tree::setPathToNode(TreeNode* node, string currpath)
{
    PathRef.insert(std::pair<int,string>(node->data,currpath));
	if(node->left!= nullptr) setPathToNode(node->left, currpath+"l");
	if(node->right!= nullptr) setPathToNode(node->right, currpath+"r");
}



//This function saves direct reference to nodes in tree
//e.g. node 5= #12h13
void Tree::setNodeRef(TreeNode *ptr)
{
  
	NodeRef.insert(std::pair<int,TreeNode *>(ptr->data,ptr));
	//  NodeVector.push_back(ptr);
}



////This function inserts new node in tree
//void Tree::insert(TreeNode *ptr)
//{
//	// NodeVector.push_back(head);// save node address in vector
//
//	Array[ptr->data]=ptr;
//	setNodeRef(ptr);   //Save reference to each inserted node
//	//setPathToNode(ptr); //Save path from head to inserted node
//	//Insertion operation :
//	if(nextNode == NULL)//if tree is empty
//	{
//		nextNode=ptr;
//		head=ptr;
//		// cout<<" "<<nextNode->data;
//	}
//	else if(nextNode->left == NULL)
//	{
//		ptr->parent = nextNode;
//		nextNode->left = ptr;
//		//cout<<" "<<nextNode->left->data;
//	}
//	else if(nextNode->right == NULL)
//	{
//		ptr->parent=nextNode;
//		nextNode->right=ptr;
//		//cout<<" "<<nextNode->right->data;
//	}
//
//	setNextNode();
//
//	size++;
//}



////This function updates pointer to a node for next insert operation
//void Tree::setNextNode()
//{
//	if(nextNode->left != NULL && nextNode->right != NULL)
//	{
//		while(nextNode->parent && nextNode->parent->right == nextNode && nextNode != head)
//		nextNode = nextNode->parent;
//
//		if(nextNode!= head)
//		{
//		nextNode=nextNode->parent;
//		nextNode=nextNode->right;
//		while(nextNode->left)
//		nextNode=nextNode->left;
//		}
//		else
//		{
//			while(nextNode->left)
//			nextNode=nextNode->left;
//		}
//
//
//	}
//}

////Prints references to each node
//void Tree::printMap()
//{
//	extern TreeNode** Array;
//	//for (std::map<int, TreeNode *>::iterator it=NodeRef.begin(); it!=NodeRef.end(); ++it)
//	//  std::cout << it->first << " => " << it->second->data << '\n';
//
//	for(int i=1;i<=10000;i++)
//	{
//	TreeNode *p = Array[i];
//	cout<< p->data <<"\n";
//	}
//}

//Prints path in lr string form
void Tree::printPath()
{
  

	for (std::map<long int, string>::iterator it=PathRef.begin(); it!=PathRef.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

}


void Tree::preorder(TreeNode *p)
{
	if(p)
	{
		cout<<" "<<p->data<<" "<<p->preNumber<<" "<<p->postNumber<<" [";
        for (int i: p->pathLabel)
            std::cout << i << ", ";
        cout<<"]"<<endl;

		if(p->left)		
		preorder(p->left);
		if(p->right)		
		preorder(p->right);
	}
}

void Tree::DFS(TreeNode* ptr)
{
	counter++;
	ptr->preNumber = counter;
	if(ptr->left != NULL)
	{
    
		DFS( ptr->left);
	}
	if(ptr->right != NULL)
	{
		DFS(ptr->right);  
	}
	counter++;
	ptr->postNumber = counter;
	
}


bool Tree::UpdateParent(TreeNode *par, TreeNode *ptr)
{
	if(par == NULL || (par->preNumber == ptr->preNumber && par->postNumber == ptr->postNumber))
	return true;

	if(par->preNumber == 0 && par->postNumber == 0)
	{
		par->preNumber = ptr->preNumber;
		par->postNumber = ptr->postNumber;	
	}
	else 
	{	
		if(par->preNumber > ptr->preNumber)
		par->preNumber = ptr->preNumber;
		if(par->postNumber < ptr->postNumber)
		par->postNumber = ptr->postNumber;	
		
	}
	
	if(par->parentUpdated)
	UpdateParent(par->parent, par);
	return true;
}


//Modified DFS algorithm for assigning intervals to data structure nodes.

void Tree::ModifiedDFS(TreeNode* ptr)
{

	// check if root is NULL
	if(ptr == NULL)
	return;

	//send updates to parent node if the node is already explored
	if(ptr->IsExplored)
	{	
		//send updates to parent node if the node is already explored
		bool ret = this->UpdateParent(ptr->parent, ptr);
		ptr->parentUpdated = (ptr->parentUpdated || ret);
		return;
	}

	//if node is a leaf node or node is a part of some cycle, consider it as leaf node and assign intervals
	if((ptr->left == NULL && ptr->right == NULL) || ptr->active)
	{
		counter++;
		ptr->preNumber = counter;
		ptr->postNumber = counter;
	}
	else
	{
		ptr->active = true;
		//call recursively modifiedDfS() function for all the child nodes. 
		//As we use binary tree, here for left and right pointers only.
		if(ptr->left !=NULL && !(ptr->left)->IsExplored)
		ModifiedDFS(ptr->left);
		if(ptr->right !=NULL && !(ptr->right)->IsExplored)
		ModifiedDFS(ptr->right);
	}

	ptr->IsExplored = true;
	ptr->active = false;
	bool ret = this->UpdateParent(ptr->parent, ptr);
	ptr->parentUpdated = (ptr->parentUpdated || ret);
	return;


}//end of modifiedDFS();


void Tree::CALabelling(TreeNode* ptr)
{
    // check if root is NULL
    if(ptr == NULL)
        return;
    if(ptr->parent==NULL){
        ptr->pathLabel.push_back(ptr->data);
        ptr->criticalAncestors.insert(ptr->data);
    } else {
        ptr->pathLabel = ptr->parent->pathLabel;
        ptr->criticalAncestors = ptr->parent->criticalAncestors;
        ptr->pathLabel.push_back(ptr->data);
        ptr->criticalAncestors.insert(ptr->data);
    }
    CALabelling(ptr->left);
    CALabelling(ptr->right);
}


//This function used by ModifiedDFS() to forward the node interval information to parent


//this function is a dummy task that can get called parallelly.
void Tree::DummyTask(int node)
{
  	int threadID = node;//temporary porvision to produce thread ID;
	//node = (node % 30) +8000;


	extern int caseParameter;
	extern int NoOfRequestedNode;
	extern int distribution;
	int accessType = 1;
  

	vector<int>NodeArray;
	int NoOfLeafNodes = LeafNodes.size()-1;
	int SlotSize = NoOfLeafNodes/distribution;
//    int SlotNo = threadID;
	int SlotNo = rand()%distribution;
    int selectStart=SlotSize*SlotNo;
    for(int i = 0;i < NoOfRequestedNode;i++)
    {
        NodeArray.push_back(LeafNodes[selectStart+i]->data);
    }

	// Intention locking ***************************************case 4
	if( caseParameter == 4)
	{
		std::map<long int,string>::iterator it;
		// sort nodes in increasing order to lock  them in order to avoid deadlock
		//sort(NodeArray, NodeArray + NoOfRequestedNode);
        counter=0;//keeps track of *ptr array indexes
        list<TreeNode *>lockNodes;
        for(auto lockObj: NodeArray)
		{
                it = PathRef.find(lockObj);
				//if(it == PathRef.end())
				//cout<<"\n"<<ReqNode;
				string path=it->second;
                TreeNode* pathNode = this->head;
		   
		     
				//if(accessType == 0)//read request
				//{
				for(int i =0; i< path.length(); i++)
				{ 
					if(accessType == 0)
					ISLock(pathNode);
					else
					IXLock(pathNode);
					if(path[i]== 'l')
					{
                        pathNode = pathNode->left;
					}
					else
					{
                        pathNode = pathNode->right;
					}
				}

                lockNodes.push_back(pathNode);
	
				if(accessType == 0)
				SLock(pathNode);
				else
				XLock(pathNode);
		}
			//Call dummay null operation
			NullOperation();
			//usleep((rand()%1000)*1000);
			//usleep(1000);
			//cout<<" coarse \n";
		
		for(auto lockedNode: lockNodes)
		{
			TreeNode * pathNode = lockedNode;
			while(pathNode != nullptr)
			{ 
				IUnLock(pathNode);
                pathNode = pathNode->parent;
			}
		}
	}
  
  // Dominator locking ***************************************case 5
	else if( caseParameter == 5)
	{//printf("\nhere tid %d\n",threadID);
		
		int min=0, max=0;
		for(auto lockObj: NodeArray)
		{
			//cout<<"\n nodes are"<<NodeArray[i]<<"\n"; 
			if(min == 0 || Array[lockObj]->preNumber < min)
			{
				min = Array[lockObj]->preNumber;
				//cout<<NodeArray[i]<<"\n";
			}
			if(max == 0 || Array[lockObj]->postNumber > max)
			{
				max = 	Array[lockObj]->postNumber;
			}
			
			
		}

        TreeNode *ptr = head;
        while( ptr->preNumber <= min && ptr->postNumber >= max)
        {
            if(ptr->left != nullptr && ptr->left->preNumber <= min && ptr->left->postNumber >= max)
            {
                ptr = ptr->left;
            }
            else if ( ptr->right != nullptr && ptr->right->preNumber <= min && ptr->right->postNumber >= max)
            {

                ptr = ptr->right;
            }
            else
            {
                break;
            }
        }


		auto *inv = new interval(ptr->preNumber,ptr->postNumber,accessType);
		xy:	if(!ICheck.IsOverlap(inv, accessType, threadID))
		{
			NullOperation();
			
			ICheck.Delete(threadID);
		}
		else{goto xy;}


   	
	}
    else if(caseParameter==7){
        list<long int> lockRequest{};
        TreeNode* lo;

        if(NodeArray.size()>1){
            for(int i : Array[NodeArray[0]]->pathLabel){
                bool allContain = true;
                for(auto lockObj: NodeArray){
                    if(!Array[lockObj]->criticalAncestors.contains(i)){
                        allContain = false;
                        break;
                    }
                }
                if(allContain){
                    lockRequest.push_back(i);
                }
            }
            lo = Array[lockRequest.back()];
        } else {
            lo = Array[NodeArray[0]];
        }

//        for(auto lockObj: NodeArray)
//        {
//            if(lockRequest.empty()){
//                lockRequest = Array[lockObj]->pathLabel;
//            } else {
//                auto it = lockRequest.begin();
//                auto end = lockRequest.end();
//                while (it != end) {
//                    if (!lockPool::hasCriticalAncestor(&Array[lockObj]->criticalAncestors, *it)) {
//                        it = lockRequest.erase(it);
//                    } else {
//                        ++it;
//                    }
//                }
//            }
//        }

        auto l = new lockObject(lo->data, &lo->criticalAncestors, accessType);
        pool.acquireLock(l, threadID);
        NullOperation();
        pool.releaseLock(threadID);
    }
    	//cout<<" \n A am in dummy task **DONE** of node:"<<node;
}
void Tree::relabelDom(TreeNode* node){

    int min = 0, max = 0;
    if(node->left != nullptr && node->right != nullptr) {
        min = node->left->preNumber;
        max = node->right->postNumber;
    }
    if(node->right !=nullptr && node->left ==nullptr) {
        min = node->right->preNumber;
        max = node->right->postNumber;
    }
    if(node->left !=nullptr && node->right ==nullptr) {
        min = node->left->preNumber;
        max = node->left->postNumber;
    }
    if(max>0 && min>0){
        node->preNumber = min;
        node->postNumber = max;
    }
    if(node->parent!= nullptr){
        relabelDom(node->parent);
    }

}
void Tree::structuralModification(int threadID){
    long int nodeInsert = NodeRef.size()+1;
    auto *newNode=new TreeNode(nodeInsert);
    newNode->pathLabel.push_back(nodeInsert);
    newNode->preNumber=nodeInsert;
    newNode->postNumber = nodeInsert;

    Array[newNode->data]=newNode;
    LeafNodes.push_back(newNode);
    setNodeRef(newNode);
    extern int caseParameter;

    if( caseParameter == 5)
    {
        //Lock the root to relabel
        auto *inv = new interval(head->preNumber,head->postNumber,1);
        xy:	if(!ICheck.IsOverlap(inv, 1, threadID))
        {
            relabelDom(newNode);
            ICheck.Delete(threadID);
        }
        else{goto xy;}
    }
    else if(caseParameter==7){
        auto l = new lockObject(newNode->data, &newNode->criticalAncestors, 1);
        pool.acquireLock(l, threadID);
        //No relabelling required since leaf insertion.
        pool.releaseLock(threadID);
//        auto lo = Array[lockRequest.back()];
//        pool.acquireLock(l, threadID);
//        NullOperation();
//        pool.releaseLock(threadID);
    }
}










