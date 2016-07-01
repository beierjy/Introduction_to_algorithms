#pragma once
template <class Type>
void insertion_sort(Type a[],size_t z)
{
	for (int i = 1; i < z; i++)
	{
		Type key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
