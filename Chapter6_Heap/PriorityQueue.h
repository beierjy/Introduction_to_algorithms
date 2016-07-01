#include "Heap.h"

using namespace std;

template<typename Type>
Type heap_exact_max(heap<Type> &a)
{
	if (a.getSize() < 1)
		throw runtime_error("heap underflow!");
	Type max = a.getArray()[0];
	a.getArray()[0] = a.getArray()[a.getSize() - 1];
	a.setSize();
	a.max_heapify(0, a.getSize());
	return max;
}

template<typename Type>
void heap_increase_key(heap<Type> &a, Type x, Type k)
{
	if (k > x)
	{
		int i = 0;
		for (; i < a.getSize(); ++i)
		{
			if (a.getArray()[i] == x)
			{
				a.getArray()[i] = k;
				break;
			}
		}
		if (i >= a.getSize())
		{
			throw runtime_error("the queue dose not contain x!");
		}
		else
		{
			while (i > 0 && a.getArray()[a.parent(i)] < a.getArray()[i])
			{
				exchange(a.getArray()[a.parent(i)], a.getArray()[i]);
				i = a.parent(i);
			}
		}
	}
}
template<typename Type>
void max_heap_insert(heap<Type> &a, Type key)
{
	a.set_size();
	heap_increase_key(a, -100, key);
}
void Test()
{
	int a[] = { 2, 3, 5, 7, 10, 8, 29, 11, 6 };
	int n = 9;
	heap<int> h(a, n);
	h.print();
	h.heapsort();
	h.print();
	heap_increase_key(h, 5, 30);
	h.print();
	max_heap_insert(h, 40);
	h.print();

}