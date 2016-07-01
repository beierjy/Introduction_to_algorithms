#ifndef LINK_H
#define LINK_H
template<class Type>
class LNode
{
public:
	LNode(){
		next = 0;
	}
	LNode(Type data, LNode *in = 0)
	{
		info = data;
		next = in;
	}
	Type info;
	LNode* next;
};

template<class Type>
class List
{
public:
	List()
	{
		head = tail = 0;
	}
	~List();
	int isEmpty()
	{
		return head == 0;
	}
	void addNode(Type);
	void addToHead(Type);
	void addToTail(Type);
	Type deleteFromHead();
	Type deleteFromTail();
	void deleteNode(Type);
	LNode<Type>* islist(Type)const;
private:
	LNode *head, *tail;
};
#endif
