#include <iostream>
#define CURRENT_SIZE 20

using namespace std;
template<typename Type>
void exchange(Type &a, Type &b)
{
	Type temp;
	temp = a;
	a = b;
	b = temp;
}
template <typename Type>
class heap
{
public:
	heap(Type* a, int n = 0) :heap_size(n)
	{
		if (n > CURRENT_SIZE)
			content = n + CURRENT_SIZE;
		else
			content = CURRENT_SIZE;
		A = new Type[content]; //这地不能再定义
		for (int i = 0; i < n; ++i)
			A[i] = a[i];
		for(int j = n; j < content; ++j)
			A[j] = 0;
	}
	~heap()
	{
		delete[] A;
	}
	void print()
	{
		for (int i = 0; i < heap_size; ++i)
			cout << A[i] <<" ";
		cout << endl;
	}
	void max_heapify(int i,int size);
	void build_max_heap(int size);
	void heapsort();
	int getSize()
	{
		return heap_size;
	}
	Type* getArray()
	{
		return A;
	}
	void setSize()
	{
		A[heap_size - 1] = 0;
		heap_size--;
	}
	void set_size()
	{
		heap_size++;
		A[heap_size - 1] = -100;	
	}
	inline int parent(int i);
	inline int left(int i);
	inline int right(int i);
private:
	int heap_size;
	int content;
	Type* A;
};
template <typename Type>
int heap<Type>::parent(int i)
{
	return ((i + 1) >> 1) - 1;
}
template <typename Type>
int heap<Type>::left(int i)
{
	return ((i + 1) << 1) - 1;
}
template <typename Type>
int heap<Type>::right(int i)
{
	return (i + 1) << 1;
}
//本程序的i是从0开始的,在维护堆的过程中，时间复杂度是O(n)，
//假设要维护的节点下面的节点全部已经是大根堆了，然后从上向下调整成大根堆。
template<typename Type>
void heap<Type>::max_heapify(int i,int size)
{
	int largest;
	while (i < size)
	{
		int l = left(i);
		int r = right(i);
		if (l <= heap_size && A[l] > A[i])
			largest = l;
		else
			largest = i;
		if (r <= heap_size && A[r] > A[largest])
			largest = r;
		if (largest != i)
			exchange(A[i], A[largest]);
		else
			break;
		i = largest;
	}
}
//从下往上建立大根堆
template<typename Type>
void heap<Type>::build_max_heap(int size)
{
	int i = size - 1;
	i = i>>1;
	while (i >= 0)
	{
		max_heapify(i,size);
		--i;
	}
}
template<typename Type>
void heap<Type>::heapsort()
{
	int n = heap_size;
	build_max_heap(n);
	Type* sorted = new Type[heap_size];
	for (int i = 0; i < heap_size; ++i)
	{
		sorted[i] = A[0];
		exchange(A[0], A[--n]); 
		A[n] = 0;
		max_heapify(0, n + 1);
	}
	for (int i = 0; i < heap_size; ++i)
		A[i] = sorted[i];
	delete[] sorted;
}
//void Test()
//{
//	int a[] = { 2, 3, 5, 7, 10, 8, 29, 11, 6 };
//	int n = 9;
//	heap<int> h(a,n);
//	h.print();
//	h.heapsort();
//	h.print();
//
//}