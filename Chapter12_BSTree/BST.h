//generic binary search tree
#include <stack>
#include <queue>

using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template <class T>
class Stack :public stack<T>
{

};
 template <class T>
 class Queue :public queue<T>{
 public:
	 T dequeue(){
		 T tmp = front();
		 queue<T>::pop();
		 return tmp;
	 }
	 void enqueue(const T& el)
	 {
		 queue<T>::push(el);
	 }
 };

 template <class T>
 class BSTNode{
 public:
	 BSTNode(){
		 left = right = 0;
	 }
	 BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T>* r = 0)
	 {
		 el = e;
		 left = l;
		 right = r;
	 }
	 T el;
	 BSTNode *left, *right;
 };

 template<class T>
 class BST{
 public:
	 BST(){
		 root = 0;
	 }
	 ~BST(){
		 clear();
	 }
	 void clear(){
		 clear(root);
		 root = 0;
	 }
	 bool isEmpty()const{
		 return root == 0;
	 }
	 void preorder(){
		 preorder(root);
	 }
	 void inorder(){
		 inorder(root);
	 }
	 void postorder(){
		 postorder(root);
	 }
	 T* search(const T& el)const{
		 return search(root, el);
	 }
	 void breadthFirst();
	 void iterativePreorder();
	 void iterativeInorder();
	 void iterativePostorder();
	 void MorrisInoder();
	 void insert(const T&);
	 void deleteByMerging(BSTNode<T>*&);
	 void findAndDeleteByMerging(const T&);
	 void deleteByCopying(BSTNode<T>*&);
	 void balance(T*, int, int);
 protected:
	 BSTNode<T>* root;
	 void clear(BSTNode<T>*);
	 T* search(BSTNode<T>*, const T&)const;
	 void preorder(BSTNode<T>*);
	 void inorder(BSTNode<T>*);
	 void postorder(BSTNode<T>*);
	 virtual void visit(BSTNode<T>*p){
		 cout << p->el << ' ';
	 }
 };
#endif