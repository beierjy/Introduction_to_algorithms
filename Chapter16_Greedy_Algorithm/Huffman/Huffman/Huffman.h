//Chapter 16 greedy algorithm
//huffman code

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <functional>

using namespace std;
typedef char Type;
struct code{
	code(int f, int d){
		freq = f;
		data = d;
	}
	int freq;
	Type data;
};
struct node{
	int key;
	struct node * m_pleft, *m_pright;
};
class com{
	bool reverse;
public:
	com(const bool& revparam = false){
		reverse = revparam;
	}
	bool operator() (const node* lhs, const node* rhs) const
	{
		if (reverse) return (lhs->key>rhs->key);
		else return (lhs->key<rhs->key);
	}

};

void Huffman(code* m_cqueue,int m_num){
	if (m_cqueue == NULL || m_num <= 0)
		return;
	//优先级队列的比较函数是类，然后类的构造函数要在后面传入；
	priority_queue<node*,vector<node*>,com> Q(com(true));

	for (int i = 0; i < m_num; i++){
		node* z = (node*)malloc(sizeof(node));
		z->key = m_cqueue[i].freq;
		z->m_pleft = z->m_pright = NULL;
		Q.push(z);
	}
	node *root = (node*)malloc(sizeof(node));
	while (!Q.empty()){
		node* z = (node*)malloc(sizeof(node));
		z->m_pleft = Q.top();
		Q.pop();
		z->m_pright = Q.top();
		Q.pop();
		z->key = z->m_pleft->key + z->m_pright->key;
		Q.push(z);
		if (Q.size() == 1){
			root = z;
			break;
		}
	}
}