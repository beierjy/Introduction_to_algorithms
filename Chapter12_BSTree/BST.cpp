#include"genBST.h"

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el)const
{
	while (p != 0)
	{
		if (el == p->el)
			return &p->el;
		else if (el < p->el)
			p = p->left;
		else
			p = p->right;
	}
}

template <class T>
void BST<T>::breadthFirst(){
	Queue<BSTNode<T>*> queue;
	BSTNode<T> *p = root;
	if (p != 0){
		queue.enqueue(p);
		while (!queue.empty()){
			p = queue.dequeue();
			visit(p);
			if (p->left != 0)
				queue.enqueue(p->left);
			if (p->right != 0)
				queue.enqueue(p->right);
		}
	}
}

template <class T>
void BST<T>::inorder(BSTNode<T> *p){
	if (p != 0)
	{
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}

template<class T>
void BST<T>::preorder(BSTNode<T> *p){
	if (p != 0){
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}

template<class T>
void BST<T>::postorder(BSTNode<T> *p){
	if (p != 0){
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}

template<class T>
void BST<T>::iterativePreorder(){
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;
	if (p != 0){
		travStack.push(p);
		while (!travStack.empty()){
			p = travStack.pop();
			visit(p);
			if (p->right != 0)
				travStack.push(p->right);
			if (p->left != 0)
				travStack.push(p->left);
		}
	}
}

template<class T>
void BST<T>::iterativePostorder(){
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root, *q = root;
	while (p != 0){
		for (; p->left != 0; p = p->left){
			travStack.push(p);
		}
		while (p->left == 0 || p->right == q){
			visit(p);
			q = p;
			if (travStack.empty())
				return;
			p = travStack.pop();
		}
		travStack.push(p);
		p = p->right;
	}
}

template<class T>
void BST<T>::iterativeInorder(){
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;
	while (p != 0){
		while (p！ = 0){ 
			if (p->right)
			travStack.push(p->right);
		travStack.push(p);
		p = p->left;
		}
		p = travStack.pop();
		while (!travStack.empty() && p->right == 0){
			visit(p);
			p = travStack.pop();
		}
		visit(p);
		if (!travStack.empty())
			p = travStack.pop();
		else
			p = 0;
	}
}

//改变树的结构来中序遍历树
template<class T>
void BST<T>::MorrisInoder(){
	BSTNode<T> *p = root, *tmp;
	while (p!=0)
		if (p->left == 0){
			visit(p);
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != 0 && tmp->right != p)
				tmp = tmp->right;
			if (tmp->right == 0){
				tmp->right = p;
				p = p->right;
			}
			else
			{
				visit(p);
				tmp->right = 0;
				p = p->right;
			}
		}
}
template<class T>
void BST<T>::insert(const T& el){
	BSTNode<T> *p = root, *prev = 0;
	while (p != 0){
		prev = p;
		if (el < p->el)
			p = p->left;
		else
			p = p->right;
	}
	if (root == 0)
		root = new BSTNode<T>(el);
	else if (el < prev->el)
		prev->left = new BSTNode<T>(el);
	else
		prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::deleteByMerging(BSTNode<T>*& node){
	BSTNode<T>* tmp = node;
	if (node != 0){
		if (!node->right)
			node = node->left;
		else if (!node->left)
			node = node->right;
		else{
			tmp = node->left;
			while (!tmp->right){
				tmp = tmp->right;
			}
			tmp->right = node->right;
			tmp = node;
			node = node->left;
		}
	}
	delete tmp;
}

template<class T>
void BST<T>::findAndDeleteByMerging(const T& k){
	BSTNode<T> *node = root, *prev = 0;
	while (node != 0){
		if (node->el == k)break;
		prev = node;
		if (node->el < k)
			node = node->right;
		else
			node = node->left;
	}
	if (node != 0 && node->el == k)
		if (node == root)
			deleteByMerging(root);
		else if (prev->left == node)
			deleteByMerging(prev->left);
		else deleteByMerging(prev->right);
	else if (root != 0)
		cout << "key" << k << " is not int the tree\n";
	else
		cout << "the tree is empty!\n";

}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>*& node){
	BSTNode<T> *previous, *tmp = node;
	if (node->right == 0)
		node = node->left;
	else if (node->left == 0)
		node = node->right;
	else
	{
		tmp = node->left;
		previous = node;
		while (tmp->right != 0){
			previous = tmp;
			tmp = tmp->right;
		}
		node->el = tmp->el;
		if (previous == node)
			previous->left = tmp->left;
		else
			previous->right = tmp->left;
	}
	delete tmp;
}
template<class T>
void BST<T>::balance(T data[], int first, int last){
	if (first <= last){
		int middle = (first + last) / 2;
		insert(data[middle]);
		balance(data, first, middle - 1);
		balance(data, middle + 1, last);
	}
}