#include"link.h"
template<class Type>
List<Type>::~List()
{
	for (LNode<Type> *p; !isEmpty();)
	{
		p = head->next;
		delete head;
		head = p;
	}
}
template<class Type>
void List<Type>::addToHead(Type data)
{
	head = new LNode<Type>(data, head);
	if (tail == 0)
		tail = head;
}
template<class Type>
void List<Type>::addToTail(Type data)
{
	if (tail != 0)
	{
		tail->next = new LNode<Type>(data);
		tail = tail->next;
	}
	else
		head = tail = new LNode<Type>(data);
}
template<class Type>
Type List<Type>::deleteFromHead()
{
	Type tmp = head->info;
	LNode<Type> *p = head;
	if (head == tail)
		head = tail = 0;
	else
		head = head->next;
	delegate p;
	return tmp;
}
template<class Type>
Type List<Type>::deleteFromTail()
{
	Type el = tail->info;
	if (head == tail)
	{
		delete head;
		head = tail = 0;
	}
	else
	{
		LNode<Type> *tmp;
		for (tmp = head; tmp->next != tail; tmp = tmp->next);
		delete tail;
		tail = tmp;
		tail->next = 0;
	}
	return el;
}

template<class Type>
void List<Type>::deleteNode(Type el)
{
	if (head != 0)
	{
		if (head == tail && el == head->info)
			delete head;
		head = tail = 0;
	}
	else if (el == head->info)
	{
		LNode<Type> *tmp = head;
		head = head->next;
		delete tmp;
	}
	else
	{
		LNode<Type> *pred, *tmp;
		for (pred = head, tmp = head->next;
			tmp != 0 && !(tmp->info == el);
			pred = pred->next, tmp = tmp->next);
		if (tmp != 0)
		{
			pred->next = tmp->next;
			if (tmp == tail)
				tail = pred;
			delete tmp;
		}
	}
}

template<class Type>
LNode<Type>* List<Type>::islist(Type el)const
{
	LNode<Type> *tmp;
	for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
	return tmp;
}
template<typename Type>
void List<Type>::addNode(Type el)
{
	LNode<Type> *tmp;
	for (tmp = head; tmp != 0 && tmp->next != islist(el); tmp = tmp->next);
	LNode<Type>* p = new LNode<Type>(el);
	p->next = tmp->next;
	tmp->next = p;
}