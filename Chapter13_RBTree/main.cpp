#include "RBTree.h"
#include <iostream>

using namespace std;

//ºìºÚÊéµÄ²âÊÔ³ÌÐò¡£
int main(){

	InitSentinel();

	RBTreeNode*   root = new RBTreeNode;
	root ->m_color = Black;
	root ->m_parent = NULL;
	root->m_pLeft = root->m_pRight = sentinel;
	root->m_value = 11;

	RBTreeNode* a1 = new RBTreeNode;
	a1->m_color = Red;
	a1->m_parent = root;
	a1->m_pLeft = a1->m_pRight = sentinel;
	a1->m_value = 2;
	root->m_pLeft = a1;

	RBTreeNode*  a2 = new RBTreeNode;
	a2->m_color = Black;
	a2->m_parent = root;
	a2->m_value = 14;
	a2->m_pLeft = a2->m_pRight = sentinel;
	root->m_pRight = a2;

	RBTreeNode*  a3 = new RBTreeNode;
	a3->m_color = Black;
	a3->m_parent = a1;
	a3->m_pLeft = a3->m_pRight = sentinel;
	a3->m_value = 1;
	a1->m_pLeft = a3;

	RBTreeNode*  a4 = new RBTreeNode;
	a4->m_color = Black;
	a4->m_parent = a1;
	a4->m_pLeft = a4->m_pRight = sentinel;
	a4->m_value = 7;
	a1->m_pRight = a4;

	RBTreeNode*  a5 = new RBTreeNode;
	a5->m_color = Red;
	a5->m_parent = a4;
	a5->m_pLeft = a5->m_pRight = sentinel;
	a5->m_value = 5;
	a4->m_pLeft = a5;
		

	RBTreeNode*  a6 = new RBTreeNode;
	a6->m_color = Red;
	a6->m_parent = a4;
	a6->m_pLeft = a6->m_pRight = sentinel;
	a6->m_value = 8;
	a4->m_pRight = a6;

	RBTreeNode*  a7 = new RBTreeNode;
	a7->m_color = Red;
	a7->m_parent = a2;
	a7->m_pLeft = a7->m_pRight = sentinel;
	a7->m_value = 15;
	a2->m_pRight = a7;

	RBTreeNode*  z = new RBTreeNode;
	z->m_color = Red;
	z->m_parent = NULL;
	z->m_pLeft = z->m_pRight = sentinel;
	z->m_value = 13;

	RBTree_Insert(root, z);

	RB_Delete(root, root);
	//cout << root->m_value << " " << root->m_pRight->m_value << " " << root->m_pRight->m_pLeft->m_value << endl;
	delete sentinel;
	delete root; delete a1; delete a2; delete a3; delete a4; delete a5; delete a6; delete a7; delete z;
	system("pause");
	return 0;
}