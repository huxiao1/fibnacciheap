/*
  Xiao Hu 69363179
 */
#include <bits/stdc++.h>
using namespace std;

class FibNode {
public:
	string   key;		//hashtag
	int      freq;		//frequency
	int      degree;	
	FibNode* left;		//left sibling
	FibNode* right;		//right sibling
	FibNode* child;		
	FibNode* parent;	
	bool     marked;
	// Create and initialize a FibNode.
	FibNode(string keyword, int val)
	{
		key    = keyword;
		freq   = val;
		degree = 0;
		marked = false;
		left   = this;
		right  = this;
		parent = nullptr;
		child  = nullptr;
	}
};

class FibHeap {
private:
	int keyNum;			//Total number of the key nodes
	int maxDegree;		//Max degree of the heap
	
	FibNode *max;		
	FibNode **cons;		//cons can store the node temporarily
	// Remove the node from the circular linked list.
	void removeNode(FibNode* node);
	
	// Cut the node.
	void cascadingCut(FibNode* node);
	
	// Increase the frequency.
	void increase(FibNode* node, int freq);
	
	// Consolidate the Fibonacci Heap which has the same degree.
	void consolidate();
	
	// Create the area for consolidation.
	void makeCons();
	
	// Extract the max node from the Fibonacci Heap.
	FibNode* extractMax();
	
	// Link the node to the root.
	void link(FibNode* node, FibNode* root);

public:

	// Create and initialize an empty Fibonacci Heap.
	FibHeap()
	{
		keyNum    = 0;
		maxDegree = 0;
		max       = nullptr;
		cons      = nullptr;
	}

	~FibHeap()
	{}
	
	// Insert the FibNode to the Fibonacci Heap.
	FibNode* insert(string key, int freq);
	
	// Update the frequency in the node.
	void update(map<string, FibNode*> &table, string key, int newfreq);
	
	// Remove the max value in Fibonacci Heap.
	FibNode* removeMax();

	
};
