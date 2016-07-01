#include <iostream>
using namespace std;

//可求整数位互不相同的数的计数排序，时间复杂都为O(n),空间复杂度为O(k);
template<typename T>
T* counter_sort(T* A,int n,T k)
{
	T* B = new T[n];
	int* C = new int[(int)k + 1];
	for (int i = 0; i <= (int)k; ++i)
		C[i] = 0;
	for (int j = 0; j < n; ++j)
		C[(int)A[j]] = C[(int)A[j]] + 1;
	
	for (int i = 1; i <= k; ++i)
		C[i] += C[i - 1];
	for (int j = n; j > 0; --j)
	{
		B[C[(int)A[j - 1]] - 1] = A[j - 1];
		C[(int)A[j - 1]] = C[(int)A[j - 1]] - 1;
	}
	delete[]C;
	return B;
}

