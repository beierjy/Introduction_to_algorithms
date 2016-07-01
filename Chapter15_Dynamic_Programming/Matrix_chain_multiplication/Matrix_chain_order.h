//矩阵链乘，求最小的括号方案
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

//非递归的链表求解，时间复杂度为O(n^3)；
void Matrix_chain_order(const int m_num, int* dim, int* m_price, int* m_split){
	if (m_num <= 0 || dim == NULL || m_price == NULL || m_split == NULL)
		return;
	for (int len = 2; len <= m_num; len++){	//len记录子链的长度
		for (int i = 1; i <= m_num - len + 1; i++){
			int j = i + len - 1;
			m_price[(i-1) * m_num + j - 1] = INT_MAX;
			for (int k = i; k < j; k++){
				int sum_price = m_price[(i-1) * m_num + k - 1] + m_price[k * m_num + j - 1] + dim[i - 1] * dim[k] * dim[j];
				if (m_price[(i- 1) * m_num + j - 1] >= sum_price){
					m_price[(i - 1) * m_num + j - 1] = sum_price;
					m_split[(i - 1) * m_num + j - 1] = k;
				}
			}
		}
	}
}
//递归求解
int recur_matrix_chain_order(const int m_num, int* dim, int* m_price, int i, int j, int* m_split){
	if (m_num <= 0 || dim == NULL || m_price == NULL||i == j)
		return  0;
	i++; j++;
	m_price[(i - 1)*m_num + j - 1] = INT_MAX;
	for (int k = i; k < j; k++){
		int sum_price = recur_matrix_chain_order(m_num, dim, m_price, i-1, k-1,m_split)
			+ recur_matrix_chain_order(m_num, dim, m_price, k, j-1,m_split) + dim[i - 1] * dim[k] * dim[j];
		if (sum_price < m_price[(i - 1)*m_num + j - 1]){
			m_price[(i - 1)*m_num + j - 1] = sum_price;
			m_split[(i - 1)*m_num + j - 1] = k;
		}
	}
	return m_price[(i - 1)* m_num + j - 1];
}
//带备忘的自顶向下的求解法
int Lookup_chain(int* m_price,int* dim,int m_num,int i,int j,int* m_split);
int memoized_matrix_chain(int m_num, int* dim,int* m_price,int* m_split){
	if (m_num <= 0 || dim == NULL||m_price == NULL || m_split == NULL)
		return 0;
	for (int i = 0; i < m_num * m_num; i++)
	{
		m_price[i] = INT_MAX;
	}
	return Lookup_chain(m_price, dim,m_num, 0, m_num - 1,m_split);
}
int Lookup_chain(int* m_price, int* dim,int m_num, int i, int j, int* m_split){
	if (m_price == NULL || dim == NULL || i < 0 || i > j || j < 0 || m_split == NULL)
		return 0;
	i++; j++;
	if (m_price[(i - 1) * m_num + j - 1] < INT_MAX)
		return m_price[(i - 1)*m_num + j - 1];
	if (i == j){
		m_price[(i - 1)*m_num + j - 1] = 0;
	}
	else{
		for (int k = i; k < j; k++){
			int sum_price = Lookup_chain(m_price,dim,m_num,i-1,k-1,m_split)
				+ Lookup_chain(m_price, dim, m_num, k, j-1, m_split) + dim[i-1] * dim[k] * dim[j];
			if (m_price[(i - 1)* m_num + j - 1] > sum_price){
				m_price[(i - 1)* m_num + j - 1] = sum_price;
				m_split[(i - 1)* m_num + j - 1] = k;
			}
		}
	}
	return m_price[(i - 1)*m_num + j - 1];
}
void print_optimal_parents(int* m_split, int i, int j, int m_num){
	if (m_split == NULL || i > j || j < 0)
		return;
	if (i == j)
		printf("A%d", i + 1);
	else
	{
		printf("(");
		print_optimal_parents(m_split, i, m_split[i * m_num + j] - 1, m_num);
		print_optimal_parents(m_split, m_split[i * m_num + j], j, m_num);
		printf(")");

	}
}
int Matrix_chain(const int m_num, int* dim){
	if (m_num <= 0 || dim == NULL)
		return 0;
	int* m_price = (int*)malloc(sizeof(int)*(m_num * m_num));
	int* m_split = (int*)malloc(sizeof(int)*(m_num * m_num));
	for (int i = 0; i < m_num * m_num; i++){
		m_price[i] = 0;
		m_split[i] = 0;
	}
	//Matrix_chain_order(m_num, dim, m_price, m_split);
	//recur_matrix_chain_order(m_num, dim, m_price, 0, m_num-1, m_split);
	memoized_matrix_chain(m_num, dim, m_price, m_split);
	for (int i = 0; i < m_num * m_num; i++){
		printf("%d\t", m_price[i]);
	}
	int min = m_price[m_num - 1];
	print_optimal_parents(m_split, 0, m_num - 1, m_num);
	printf("\n%d", min);
	free(m_price);
	free(m_split);
	return min;
}



