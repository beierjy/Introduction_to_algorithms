#pragma once
#include <iostream>
using namespace std;

template <class Type>
void merge(Type a[], int p, int q, int r)
{
	
	int n1 = q - p + 1;
	int n2 = r - q;
	Type * L = new Type[n1 + 1];
	Type * R = new Type[n2 + 1];
	for (int i = 0; i < n1 ; i++)
		L[i] = a[p + i -1];
	for (int i = 0; i < n2; i++)
		R[i] = a[q + i];

	int i = 0;
	int j = 0;
	L[n1] = '{';
	R[n2] = '{';
	
	for (int k = p - 1; k < r; k++)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
				j++;
		}
	}
	delete L;
	delete R;
	
}
template <class Type>
void merge_sort( Type a[],int p, int r)
{
	if (p < r)
	{
		int q = (r + p) / 2;
		merge_sort(a, p, q);
		merge_sort(a, q + 1, r);
		merge(a, p, q, r);
	}
	cout << "\n**********" << endl;
	for (int i = 0; i < r; i++)
	{
		cout << a[i] << " ";
	}
}
