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
RBTreeNode* sentinel = new RBTreeNode;//�ڱ�
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
//�����������������
void RBTree_Insert_FixUp(RBTreeNode** pRoot, RBTreeNode* Node){
	RBTreeNode* y = sentinel;//��¼������
	while (Node->m_parent->m_color == Red){
			if (Node->m_parent->m_parent->m_pRight != sentinel){
				y = Node->m_parent->m_parent->m_pRight;
				//case1: Node �ڵ�ΪRed������ڵ����ɫ��Red����ʱ�ı丸�׺�����ڵ�Ϊ��ɫ����үү�ڵ�Ϊ��ɫ����ʱ
				//���ܸı���үү����үү�Ĺ�ϵ��������үү�ڵ�ΪNode�ڵ�
				if (y->m_color == Red){
					Node->m_parent->m_color = Black;
					y->m_color = Black;
					Node->m_parent->m_parent->m_color = Red;
					Node = Node->m_parent->m_parent;
					continue;
				}
				//case2: �������ڵ���Black���Ҵ�ʱ�ڵ�Ϊ���׽ڵ���Һ��ӣ���ת�ı����Ϊ�ڵ������
				else if (Node == Node->m_parent->m_pRight){
					Node = Node->m_parent;
					LeftRotate(pRoot, Node);
				}
				//case3:�����ڵ��Ǻ�ɫ����ǰ����Ǹ��ڵ�����
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
//���ڵ�ժ��
void RB_Transplant(RBTreeNode* &pRoot, RBTreeNode* u, RBTreeNode* v){
	if (u->m_parent == NULL)
		pRoot = v;
	else if (u == u->m_parent->m_pLeft)
		u->m_parent->m_pLeft = v;
	else
		u->m_parent->m_pRight = v;
	v->m_parent = u->m_parent;
}
//�����������Сֵ
RBTreeNode* Tree_Minimum(RBTreeNode* Node){
	RBTreeNode* Temp = Node;
	while (Temp->m_pLeft != sentinel)
		Temp = Temp->m_pLeft;
	return Temp;
}
void RB_Delete_Fixup(RBTreeNode** pRoot, RBTreeNode* Node){
	RBTreeNode* w = sentinel;//��¼������
	while (Node != *pRoot && (Node->m_color == Black || Node == sentinel)){
		//Node���丸�ڵ������������
		if (Node == Node->m_parent->m_pLeft){
			w = Node->m_parent->m_pRight;
			//case1:Node���ֵܽڵ��Ǻ�ɫ����������Node�ĸ��ڵ��������ת��Ȼ���丸�ڵ����ɫ���ֵܽڵ��ཻ��
			//��ʱNode��һ����ɫ���ֵܽڵ㣬���Խ���������������ۡ�
			if (w->m_color == Red){
				w->m_color = Black;
				Node->m_parent->m_color = Red;
				LeftRotate(pRoot, Node->m_parent);
				w = Node->m_parent->m_pRight;
				continue;
			}
			//case2:Node�Ľڵ���ֵܽڵ���������Ӷ��Ǻ�ɫ�������ֵܽڵ㱾��Ҳ�Ǻ�ɫ����ʱ�����ֵܽڵ�ı�ɺ�ɫ�����ƻ��˺���Node
			//�ĸ��ڵ��·���ϵĺ�ɫ�ڵ�ĸ�������ʱӦ�ý�Node�任ΪNode�ĸ��׽ڵ㣬�Ե����丸�׽ڵ��ƽ�⣬Node��ʱ�Ѿ�ƽ��
			if ((w->m_pLeft->m_color == Black && w->m_pRight->m_color == Black) || 
				(w->m_pLeft == sentinel || w->m_pRight == sentinel)){
				w->m_color = Red;
				Node = Node->m_parent;
			}
			//case3:��ʱNode���ֵܽڵ��Ǻ�ɫ��������Ů����ɫҲ�Ǻ�ɫ������Ϊ��ɫ,����������ת�������ֵܽڵ�
			else if (w->m_pRight->m_color == Black){
				w->m_pLeft->m_color = Black;
				w->m_color = Red;
				RightRotate(pRoot, w);
				w = Node->m_parent->m_pRight;
			}
			//case4:��ʱ������������ֵܽڵ���������Ӷ��Ǻ�ɫ�ģ����������Ǻ�ɫ�ģ��Һ����Ǻ�ɫ��
			//���ֵܽڵ����ɫ�븸�׽ڵ㽻��,Ȼ��ʹ��s���Һ���Ϊ��ɫ��Ȼ������Node������ת������֮�����еĽڵ�·���ϵ����ʶ��õ��˱���
			//��������������ʹ��ѭ��������
				w->m_color = Node->m_parent->m_color;
				Node->m_parent->m_color = Black;
				w->m_pRight->m_color = Black;
				LeftRotate(pRoot, Node->m_parent);
				Node = *pRoot;
		}
		//ͬ��NodeΪ��������
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
	RBTreeNode* y = Node;    //��¼Ҫɾ���Ľڵ�λ�ã�Ȼ�����滻���������������ɫ�����Ƿ���Ҫ����
	RBTreeNode* x = sentinel;  //��¼Ҫɾ���ڵ���滻�ڵ㣬Ȼ��ýڵ����㷨����������Ϊ������ɫ����Ҫȥ��һ��ԭy����ɫ��������Ҫ���ֺ��������
	int y_color = y->m_color;   //��¼ɾ���ڵ����ɫ��
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
		if (y->m_parent == Node)// ���yǡ����Node�ڵ���Һ��ӣ���ʱx�ڵ�ĸ��׽ڵ����y�ڵ㡣
		{
			x->m_parent = y;
		}
		else{                   //���򣬽���y��x��λ�ã���y�ڵ��Ƴ�
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
