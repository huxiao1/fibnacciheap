/*
  Xiao Hu 69363179
 */
#include <bits/stdc++.h>
#include "FibonacciHeap.h"
using namespace std;
//Insert the fibnode to the fibonacci heap.
FibNode* FibHeap::insert(string key, int freq) {
	FibNode *node = new FibNode(key, freq);
	if (node == nullptr)
		return nullptr;
	if (!keyNum)
		max = node;
	else {
		node->left        = max->left;
		max->left->right  = node;
		node->right       = max;
		max->left         = node;		
		if (node->freq > max->freq)
			max = node;
	}
	++keyNum;
	return node;
}

//Remove the node from the circular linked list.
void FibHeap::removeNode(FibNode* node) {
	node->left->right = node->right;
	node->right->left = node->left;
	return;
}

//cascadingCut use cut until the false node
void FibHeap::cascadingCut(FibNode* node) {
	FibNode* parent = node->parent;
	if (parent != nullptr) {
		if (node->marked == false) 
			node->marked = true;
		else {
			
			removeNode(node);
			parent->degree=parent->degree-1;
	
			if (node == node->right) 
				parent->child = nullptr;
			else 
				parent->child = node->right;
			node->parent = nullptr;
			node->left = node->right = node;
			node->marked = false;
	
			node->left        = max->left;
			max->left->right  = node;
			node->right       = max;
			max->left         = node;

			cascadingCut(parent);
		}
	}
	return;
}

//Increase the frequency.
void FibHeap::increase(FibNode* node, int freq) {
	FibNode* parent;
	
	if (max == nullptr || node == nullptr)
		return;
	
	node->freq = node->freq + freq;
	
	parent = node->parent;
	if (parent != nullptr && node->freq > parent->freq) {
		
		removeNode(node);
		parent->degree=parent->degree-1;
	
		if (node == node->right) 
			parent->child = nullptr;
		else 
			parent->child = node->right;
		node->parent = nullptr;
		node->left = node->right = node;
		node->marked = false;
		node->left        = max->left;
		max->left->right  = node;
		node->right       = max;
		max->left         = node;		
		cascadingCut(parent);
	}
	
	if (node->freq > max->freq)
		max = node;
	
	return;
}

//Update the frequency in the node.
void FibHeap::update(map<string, FibNode*> &table, string key, int newfreq) {
	if (table[key] != nullptr)
		increase(table[key], newfreq);
	return;
}

//Extract the max node from the Fibonacci Heap.
FibNode* FibHeap::extractMax() {
	FibNode* p = max;
	if (p == p->right)
		max = nullptr;
	else {
		removeNode(p);
		max = p->right;
	}
	p->left = p->right = p;
	return p;
}
	
//Link the node to the root.
void FibHeap::link(FibNode* node, FibNode* root) {
	removeNode(node);
	if (root->child == nullptr)
		root->child = node;
	else
		node->left        = root->child->left;
		root->child->left->right  = node;
		node->right       = root->child;
		root->child->left         = node;
	
	node->parent = root;
	++root->degree;
	node->marked = false;
	
	return;
}

//Create the area for consolidation.
void FibHeap::makeCons() {
	int old = maxDegree;
	
	maxDegree = (log(keyNum) / log(2.0)) + 1;
	if (old >= maxDegree)
		return ;
	cons = new FibNode*[maxDegree + 1];
	
	return;
}

//Consolidate the Fabonacci Heap which has the same degree.
void FibHeap::consolidate() {
	int i, d, D;
	FibNode *x, *y, *tmp;
	
	
	int old = maxDegree;
	
	maxDegree = (log(keyNum) / log(2.0)) + 1;
	if (old >= maxDegree)
		i = 1;
	cons = new FibNode*[maxDegree + 1];
	D = maxDegree + 1;

	for (i = 0; i < D; i++)
		cons[i] = nullptr;
  
	while (max != nullptr) {
		
		x = extractMax();
		d = x->degree;
	
		while (cons[d] != nullptr) {
			y = cons[d];
			
			if (x->freq < y->freq)
				swap(x, y);
 
			link(y, x); 
			cons[d] = nullptr;
			++d;
		}
		cons[d] = x;
	}
	max = nullptr;
	// Put the node in the cons to the cycle linked list.
	for (i = 0; i < D; ++i) {
		if (cons[i] != nullptr) {
			if (max == nullptr)
				max = cons[i];
			else {
				cons[i]->left        = max->left;
				max->left->right  = cons[i];
				cons[i]->right       = max;
				max->left         = cons[i];
				if ((cons[i])->freq > max->freq)
					 max = cons[i];
			}
		}
	}
	return;
}

//Remove the max in Fibonacci Heap.
FibNode* FibHeap::removeMax() {
	if (max == nullptr)
		return nullptr;
	
	FibNode* child = nullptr;
	FibNode* m     = max;
	FibNode* ret   = new FibNode(max->key, max->freq);
	
	while (m->child != nullptr) {
		child = m->child;
		removeNode(child);
		
		if (child->right == child)
			m->child = nullptr;
		else
			m->child = child->right;
		
		child->left        = max->left;
		max->left->right  = child;
		child->right       = max;
		max->left         = child;
		child->parent = nullptr;
	}
	
	removeNode(m);
	if (m->right == m)
		max = nullptr;
	else {
		max = m->right;
		consolidate();
	}
	--keyNum;
	delete m;
	
	return ret;
}
