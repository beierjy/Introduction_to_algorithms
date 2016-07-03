//Chapter 16 greedy algorithm
//activity selector 
#include <stdio.h>
#include <stdlib.h>

void recursive_activity_selector(int* start, int* finish, int* result, int k, int n,int& pos){
	if (start == NULL || finish == NULL || result == NULL || k < 0 || n <= 0 || k > n || pos < 0)
		return;
	int m = k + 1;
	while (m <= n && start[m] < finish[k])
		m++;
	if (m <= n)
	{
		result[pos++] = m;
		recursive_activity_selector(start, finish, result, m, n, pos);
	}
	else
		return;
}
void greedy_activity_selector(int* start, int* finish, int* result,int len){
	if (start == NULL || finish == NULL || result == NULL)
		return;
	int k = 1; int m = 1; int pos = 1;
	result[0] = m;
	m++;
	while (m <= len){
		if (start[m] >= finish[k]){
			result[pos++] = m;
			k = m;
		}
		m++;
	}
	return;
}
void selector(int* start, int* finish, int len){
	if (start == NULL || finish == NULL || len < 0)
		return;
	int* result = (int*)malloc(sizeof(int)*len);
	for (int i = 0; i < len; i++){
		result[i] = 0;
	}
	int pos = 0;
	//recursive_activity_selector(start, finish, result, 0, len, pos);
	greedy_activity_selector(start, finish, result, len);
	for (int i = 0; i < len; i++){
		if (result[i] != 0)
			printf("%d ", result[i]);
	}
	return;
}