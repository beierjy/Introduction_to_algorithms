//Generic binary search threaded tree
#include <iostream>

using namespace std;

#ifndef THREADED_TREE
#define THREADED_TREE

template<class T>
class ThreadedNode{
public:
	ThreadedNode(){
		left = right = 0;
	}
	ThreadedNode(const T&e, ThreadedNode *l = 0, ThreadedNode* r = 0){
		el = e;
		left = l;
		right = r;
		successor = 0;
	}
	T el;
	ThreadedNode *left, *right;
	unsigned int successor : 1;
};

template<class T>
class ThreadedTree{
public:
	ThreadedTree(){
		root = 0;
	}
	void insert(const T&);
	void inorder();
protected:
	ThreadedNode<T>* root;
};
template<class T>
void visit(ThreadedNode<T>* p)
{
	cout << p->el << ' ';
}
#endif