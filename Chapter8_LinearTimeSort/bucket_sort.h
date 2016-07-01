#include <iostream>

using namespace std;
typedef double  Type;
typedef struct Node
{
	Type data;
	struct Node* next;
}linknode, *linklist;

void init(linklist &first)
{
	first = new linknode;
	first->data = 0;
	first->next = NULL;
}
void insert(linklist& first,Type t)
{
	linknode* is = new linknode;
	if (!is)
	{
		throw runtime_error("new failed ");
	}
	linknode* pre = first;
	is->data = t;
	is->next = pre->next;
	pre->next = is;
}

void insert_sort(linklist& A)
{
	linknode* p = A->next;
	linknode* pre = A;
	while (p != NULL)
	{
		linknode* sortedpre = A;
		linknode* sorted = A->next;
		while (p != NULL && sorted != p && sorted->data < p->data)
		{
			sortedpre = sorted;
			sorted = sorted->next;
		}
		if (sorted != p)
		{
			pre->next = p->next;
			p->next = sorted;
			sortedpre->next = p;
			p = pre->next;
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}
void bucket_sort(Type* A, int n, int t)
{
	int tmp;
	linklist*B = new linklist[t];
	for (int i = 0; i < t; ++i)
	{
		init(B[i]);
	}
	for (int i = 0; i < n; i++)
	{
		tmp = n * A[i];
		insert(B[tmp], A[i]);
	}
	for (int i = 0; i < t; ++i)
	{
		insert_sort(B[i]);
	}
	int j = 0;
	for (int i = 0; i < t; ++i)
	{
		linknode* pre = B[i]->next;
		while (pre != NULL)
		{
			A[j++] = pre->data;
			pre = pre->next;
		}
	}
	delete B;
}
