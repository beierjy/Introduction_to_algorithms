#include <iostream>
#include <stack>
#include <cstdlib>
#include <time.h>

using namespace std;
template<typename Type>
void exchange(Type &a,Type 
	
	)
{
	Type temp;
	temp = a;
	a = b;
	b = temp;
}

//一次扫描，从左向右，小于最后的那个值得都交换，最终得到最后那个位置的数的最终位置,O(1);
template<typename Type>
size_t partition(Type* A, size_t left, size_t right)
{
	Type temp = A[right];
	size_t i = left;
	for (int j = left; j < right; ++j)
	{
		if (A[j] <= temp)
		{
			exchange(A[i++], A[j]);
		}
	}
	exchange(A[i], A[right]);
	return i;
}
//随机化版本，每次选择的主元为随机选择
template<typename Type>
size_t random_partition(Type* A, size_t left, size_t right)
{
	srand(time(NULL));
	size_t index;
	index = rand() % (right - left)+left;
	exchange(A[index], A[right]);
	return partition(A, left, right);
}
template<typename Type>
void recur_quicksort(Type* A, size_t left, size_t right)
{
	if (A == NULL || left < 0 || right < 0)
		exit(1);
	size_t p;
	if (left < right)
	{
		p = random_partition(A, left, right);
		recur_quicksort(A, left, p - 1);
		recur_quicksort(A, p + 1, right);
	}
}
//迭代法求快速排序需要用到栈
template<typename Type>
void iteration_quiksort(Type* A,int  n)
{
	if (n <= 1)
		return;
	stack<int> ranges;
	Type pivot;
	int temp;
	int l = 0, r = n;
	int tr, tl;
	ranges.push(l);
	ranges.push(r);
	while (!ranges.empty())
	{
		tr = r = ranges.top();
		ranges.pop();
		tl = l = ranges.top();
		ranges.pop();
		srand(time(NULL));
		size_t i;
		while (true)
		{
			i = rand() % (r + 1) - 1;
			if (i >= tl && i <= tr)
				break;
		}
		exchange(A[i], A[tl]);
		pivot = A[tl];
		temp = tl;
		if (r - l <= 1)
			continue;
		while (tr > tl)
		{
			while (tr > tl && A[--tr] > pivot);
			//A[tl] = A[tr];
			while (tr > tl && A[++tl] < pivot);
			//A[tr] = A[tl];
			exchange(A[tr], A[tl]);

		}
		//A[tl] = pivot;
		exchange(A[tl], A[temp]);
		ranges.push(l);
		ranges.push(tl);
		ranges.push(tl + 1);
		ranges.push(r);
	}
}
void Test()
{
	int a[] = { 1, 6, 6, 2, 3, 3, 5, 8, 7 };
	recur_quicksort(a, 0, 8);
	//iteration_quiksort(a, 9);
	for (int i = 0; i < 9; ++i)
		cout << a[i] << " ";
}
