#include"genThreaded.h"
template<class T>
void ThreadedTree<T>::inorder(){
	ThreadedNode<T> *prev, *p = root;
	if (p != 0){
		while (p->left != 0)
			p = p->left;
		while (p != 0){
			visit(p);
			prev = p;
			p = p->right;
			if (p != 0 && prev->successor == 0)
				while (p->left != 0)
					p = p->left;
		}
	}
}