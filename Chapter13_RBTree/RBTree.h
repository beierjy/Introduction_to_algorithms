//Introduction to Algorithms chapter 13
//this is the Red and Block Tree
#ifndef RBTREE_H
#define RBTREE_H
#include <cstdlib>

typedef int Type;
enum color{ Red ,Black };

struct RBTreeNode{
	int m_color;
	RBTreeNode* m_pLeft;
	RBTreeNode* m_pRight;
	RBTreeNode* m_parent;
	Type m_value;
};
RBTreeNode* sentinel = new RBTreeNode;//哨兵
void InitSentinel(){
	sentinel->m_color = Black;
	sentinel->m_parent = NULL;
	sentinel->m_value = 0x8FFFFFFF;
	sentinel->m_pLeft = sentinel->m_pRight = NULL;
}
typedef struct RBTree{
	RBTreeNode* rb_tree;
};

void LeftRotate(RBTreeNode** pRoot,RBTreeNode* pNode){
	RBTreeNode* right = pNode->m_pRight;
	pNode->m_pRight = right->m_pLeft;
	if (right->m_pLeft != sentinel)
		right->m_pLeft->m_parent = pNode;
	right->m_parent = pNode->m_parent;
	if (pNode->m_parent == NULL)
		*pRoot = right;
	else if (pNode == pNode->m_parent->m_pLeft)
		pNode->m_parent->m_pLeft = right;
	else
		pNode->m_parent->m_pRight = right;
	right->m_pLeft = pNode;
	pNode->m_parent = right;
}

void RightRotate(RBTreeNode** pRoot, RBTreeNode* pNode){
	RBTreeNode* left = pNode->m_pLeft;
	pNode->m_pLeft = left->m_pRight;
	if (left->m_pRight != sentinel)
		left->m_pRight->m_parent = pNode;
	left->m_parent = pNode->m_parent;
	if (pNode->m_parent == NULL)
		*pRoot = left;
	else if (pNode == pNode->m_parent->m_pRight)
		pNode->m_parent->m_pRight = left;
	else
		pNode->m_parent->m_pRight = left;
	pNode->m_parent = left;
	left->m_pRight = pNode;
}
//插入操作的修正操作
void RBTree_Insert_FixUp(RBTreeNode** pRoot, RBTreeNode* Node){
	RBTreeNode* y = sentinel;//记录叔叔结点
	while (Node->m_parent->m_color == Red){
			if (Node->m_parent->m_parent->m_pRight != sentinel){
				y = Node->m_parent->m_parent->m_pRight;
				//case1: Node 节点为Red，叔叔节点的颜色是Red，此时改变父亲和叔叔节点为黑色，让爷爷节点为红色，此时
				//可能改变了爷爷和祖爷爷的关系，故设置爷爷节点为Node节点
				if (y->m_color == Red){
					Node->m_parent->m_color = Black;
					y->m_color = Black;
					Node->m_parent->m_parent->m_color = Red;
					Node = Node->m_parent->m_parent;
					continue;
				}
				//case2: 如果叔叔节点是Black，且此时节点为父亲节点的右孩子，旋转改变其成为节点的左孩子
				else if (Node == Node->m_parent->m_pRight){
					Node = Node->m_parent;
					LeftRotate(pRoot, Node);
				}
				//case3:叔树节点是黑色，当前结点是父节点左孩子
				Node->m_parent->m_color = Black;
				Node->m_parent->m_parent->m_color = Red;
				RightRotate(pRoot, Node->m_parent->m_parent);
			}
		else{
				y = Node->m_parent->m_parent->m_pLeft;
				if (y->m_color == Red){
					Node->m_parent->m_color = Black;
					y->m_color = Black;
					Node->m_parent->m_parent->m_color = Red;
					Node = Node->m_parent->m_parent;
					continue;
				}
				else if (Node == Node->m_parent->m_pLeft){
					Node = Node->m_parent;
					RightRotate(pRoot, Node);
				}
				Node->m_parent->m_color = Black;
				Node->m_parent->m_parent->m_color = Red;
				LeftRotate(pRoot, Node->m_parent->m_parent);
			}
		}
	(*pRoot)->m_color = Black;
}
void RBTree_Insert(RBTreeNode* &pRoot, RBTreeNode* Node){
	RBTreeNode* y = sentinel;
	RBTreeNode* x = pRoot;
	while (x != sentinel){
		y = x;
		if (Node->m_value < x->m_value)
			x = x->m_pLeft;
		else
			x = x->m_pRight;
	}
	Node->m_parent = y;
	if (y == sentinel)
		pRoot = Node;
	else if (Node->m_value < y->m_value)
		y->m_pLeft = Node;
	else
		y->m_pRight = Node;
	Node->m_pLeft = sentinel;
	Node->m_pRight = sentinel;
	Node->m_color = Red;
	RBTree_Insert_FixUp(&pRoot, Node);
}
//将节点摘除
void RB_Transplant(RBTreeNode* &pRoot, RBTreeNode* u, RBTreeNode* v){
	if (u->m_parent == NULL)
		pRoot = v;
	else if (u == u->m_parent->m_pLeft)
		u->m_parent->m_pLeft = v;
	else
		u->m_parent->m_pRight = v;
	v->m_parent = u->m_parent;
}
//获得子树的最小值
RBTreeNode* Tree_Minimum(RBTreeNode* Node){
	RBTreeNode* Temp = Node;
	while (Temp->m_pLeft != sentinel)
		Temp = Temp->m_pLeft;
	return Temp;
}
void RB_Delete_Fixup(RBTreeNode** pRoot, RBTreeNode* Node){
	RBTreeNode* w = sentinel;//记录叔叔结点
	while (Node != *pRoot && (Node->m_color == Black || Node == sentinel)){
		//Node在其父节点的左子树上面
		if (Node == Node->m_parent->m_pLeft){
			w = Node->m_parent->m_pRight;
			//case1:Node的兄弟节点是红色，将其沿着Node的父节点进行左旋转，然后将其父节点的颜色与兄弟节点相交换
			//此时Node有一个黑色的兄弟节点，可以进行下面情况的讨论。
			if (w->m_color == Red){
				w->m_color = Black;
				Node->m_parent->m_color = Red;
				LeftRotate(pRoot, Node->m_parent);
				w = Node->m_parent->m_pRight;
				continue;
			}
			//case2:Node的节点的兄弟节点的两个孩子都是黑色，而其兄弟节点本身也是黑色，此时将其兄弟节点改变成红色，则破坏了含有Node
			//的父节点的路径上的黑色节点的个数，此时应该将Node变换为Node的父亲节点，以调整其父亲节点的平衡，Node此时已经平衡
			if ((w->m_pLeft->m_color == Black && w->m_pRight->m_color == Black) || 
				(w->m_pLeft == sentinel || w->m_pRight == sentinel)){
				w->m_color = Red;
				Node = Node->m_parent;
			}
			//case3:此时Node的兄弟节点是黑色，其右子女的颜色也是黑色，左孩子为红色,则先行右旋转，更新兄弟节点
			else if (w->m_pRight->m_color == Black){
				w->m_pLeft->m_color = Black;
				w->m_color = Red;
				RightRotate(pRoot, w);
				w = Node->m_parent->m_pRight;
			}
			//case4:此时的情况可能是兄弟节点的两个孩子都是红色的，或者左孩子是黑色的，右孩子是红色的
			//将兄弟节点的颜色与父亲节点交换,然后使得s的右孩子为黑色，然后沿着Node向左旋转，这样之后所有的节点路径上的性质都得到了保持
			//现在设置条件，使得循环跳出。
				w->m_color = Node->m_parent->m_color;
				Node->m_parent->m_color = Black;
				w->m_pRight->m_color = Black;
				LeftRotate(pRoot, Node->m_parent);
				Node = *pRoot;
		}
		//同理Node为其右子树
		else{
			w = Node->m_parent->m_pLeft;
			if (w->m_color == Red){
				w->m_color = Black;
				Node->m_parent->m_color = Red;
				RightRotate(pRoot, Node->m_parent);
				w = Node->m_parent->m_pLeft;
				continue;
			}
			if ((w->m_pLeft->m_color == Black && w->m_pRight->m_color == Black) ||
				(w->m_pLeft == sentinel || w->m_pRight == sentinel)){
				w->m_color = Red;
				Node = Node->m_parent;
			}
			else if (w->m_pLeft->m_color == Black){
				w->m_pRight->m_color = Black;
				w->m_color = Red;
				LeftRotate(pRoot, w);
				w = Node->m_parent->m_pLeft;
			}

				w->m_color = Node->m_parent->m_color;
				Node->m_parent->m_color = Black;
				w->m_pLeft->m_color = Black;
				RightRotate(pRoot, Node->m_parent);
				Node = *pRoot;
		}
	}
	if (Node != sentinel)
		Node->m_color = Black;
}
void RB_Delete(RBTreeNode* &pRoot, RBTreeNode* Node){
	RBTreeNode* y = Node;    //记录要删除的节点位置，然后先替换他，最后检查它的颜色，看是否需要调整
	RBTreeNode* x = sentinel;  //记录要删除节点的替换节点，然后该节点在算法导论上描述为多重颜色，需要去掉一层原y的颜色，并且需要保持红黑树性质
	int y_color = y->m_color;   //记录删除节点的颜色；
	if (Node->m_pLeft == sentinel){
		x = Node->m_pRight;
		RB_Transplant(pRoot, Node, Node->m_pRight);
	}
	else if (Node->m_pRight == sentinel){
		x = Node->m_pLeft;
		RB_Transplant(pRoot, Node, Node->m_pLeft);
	}
	else{
		y = Tree_Minimum(Node->m_pRight);
		y_color = y->m_color;
		x = y->m_pRight;
		if (y->m_parent == Node)// 如果y恰好是Node节点的右孩子，此时x节点的父亲节点便是y节点。
		{
			x->m_parent = y;
		}
		else{                   //否则，交换y和x的位置，将y节点移出
			RB_Transplant(pRoot, y, x);
			y->m_pRight = Node->m_pRight;
			y->m_pRight->m_parent = y;
		}
		RB_Transplant(pRoot, Node, y);
		y->m_pLeft = Node->m_pLeft;
		y->m_pLeft->m_parent = y;
		y->m_color = Node->m_color;
		
	}
	if (y_color == Black)
		RB_Delete_Fixup(&pRoot, x);
}
#endif
