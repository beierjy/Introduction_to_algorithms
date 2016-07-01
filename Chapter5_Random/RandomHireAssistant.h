#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;
template <typename Type>
void permute_by_sorting(Type* A,size_t n)
{
	srand((unsigned)time(0));
	Type temp; int ptm;
	int* p= new int[n];
	for (int i = 0; i < n; ++i)
	{
		p[i] = rand() % (n*n*n);//n^3在c++里不能这样表示
		cout << p[i]<<" ";
	}
	//使用ptem作为排序码，将A进行排序
	for (int i = 1; i < n; i++)
	{	
		ptm = p[i];
		temp = A[i];
		int j = i - 1;
		while (j >= 0)// 注意条件是是否跳过了j = 0的点。
		{
			
			if (ptm < p[j])
			{
				p[j + 1] = p[j];
				A[j + 1] = A[j];
			}
			else
			{
				break;
			}	
			--j;
		}
		p[j + 1] = ptm;
		A[j + 1] = temp;
	}
	cout << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << p[i]<<" ";
	}
	delete []p;
}
template <typename Type>
void random(Type *A, int n)
{
	Type temp;
	for (int i = 0; i < n; ++i)
	{
		temp = A[i];
		int j = (rand() % (n - i)) + i;//这里求一定范围内的随机产生数字
		A[i] = A[j];
		A[j] = temp;
	}
}
int random_hire_assistant(int n)
{
	int a[] = {1,5,10,25,9,2,45,3,4,15,8,12};
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	/*permute_by_sorting(a, n);*/
	random(a, n);
	cout << endl;
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";

	int interfee = 50;
	int empfee = 200;
	int best = 0;
	int hirefee = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] > best)
		{
			best = a[i];
			hirefee += interfee + empfee;
		}
		else
			hirefee += interfee;
	}
	return hirefee;
}