//Chapter15 Dynamic algorithm
//0_1 knapsack problem 

#include <stdio.h>
#include <stdlib.h>


int _0_1_knapsack_up(int* weight, int* price, int m_num, int w_sum,int k,int l, int* sum_price){
	if (weight == NULL || price == NULL || m_num <= 0 || w_sum <= 0|| sum_price == NULL ||k < 0 || l < 0 ||k > l)
		return 0;
	if (k == l && w_sum -weight[k] >= 0){
		return price[l];
	}
	int temp_p = 0; int max_sum = 0;
	for (int i = k; i <= l; ++i){
		if (w_sum - weight[i] >= 0){
			temp_p = price[i] + _0_1_knapsack_up(
				weight, price,m_num,w_sum - weight[i], i + 1, l, sum_price);
		}
		if (temp_p > max_sum){
			max_sum = temp_p;
		}
	}
	return max_sum;
}
void recur_0_1_knapsack(int* weight, int* price, int m_num, int w_sum){
	if (weight == NULL || price == NULL || m_num <= 0 || w_sum <= 0)
		return;
	int* sum_price = (int*)malloc(sizeof(int)*(m_num*m_num));
	for (int i = 0; i < m_num*m_num; i++){
		sum_price[i] = 0;
	}
	int max = _0_1_knapsack_up(weight, price, m_num, w_sum,0,m_num-1, sum_price);
	for (int i = 0; i < m_num * m_num; i++){
		printf("%d ", sum_price[i]);
	}
	free(sum_price);
}

//迭代求解法
void _0_1_knapsack_1(int* weight, int* price, int m_num, int w_sum){
	if (weight == NULL || price == NULL || m_num <= 0 || w_sum <= 0)
		return;
	int** m_price = (int**)malloc(sizeof(int*)*m_num);
	for (int i = 0; i < m_num; i++){
		m_price[i] = (int*)malloc(sizeof(int)*m_num);
	}
	int** w_l = (int**)malloc(sizeof(int*)*m_num);
	for (int i = 0; i < m_num; i++){
		w_l[i] = (int*)malloc(sizeof(int)*m_num);
	}
	for (int i = 0; i < m_num; i++){
		for (int j = 0; j < m_num; j++){
			if (i == j && weight[i] <= w_sum){
				m_price[i][j] = price[i];
				w_l[i][j] = w_sum - weight[i];
			}
			else
				m_price[i][j] = 0;
		}
	}
	int max = m_price[0][0]; 
	int tag = 0;
	for (int i = 0; i < m_num; i++){
		for (int j = i+1; j < m_num; j++){
			if (weight[j] > w_l[i][j-1]){
				m_price[i][j] = m_price[i][j - 1];
				w_l[i][j] = w_l[i][j - 1];
			}
			else{
				int temp_price = m_price[i][j - 1] + price[j];
				if (temp_price > m_price[i][j - 1]){
					m_price[i][j] = temp_price;
					w_l[i][j] = w_l[i][j - 1] - weight[j];
				}
				if (max < m_price[i][j]){
					max = m_price[i][j];
					tag = i;
				}
			}
		}
	}
	for (int i = tag; i < m_num; i++){
		for (int j = i; j < m_num; j++){
			if (j > 0 && m_price[i][j] != m_price[i][j - 1])
				printf("%d\t", j + 1);
		}
	}
	printf("\n%d", max);
	printf("\n");
	for (int i = 0; i < m_num; i++){
		for (int j = 0; j < m_num; j++){
				printf("%d\t", m_price[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < m_num; i++){
		free(m_price[i]);
	}
	free(m_price);
	for (int i = 0; i < m_num; i++){
		free(w_l[i]);
	}
	free(w_l);
}

//动态规划
int min_fun(int m, int n){
	if (m > n)
		return n;
	else
		return m;
}
int max_fun(int m, int n){
	if (m > n)
		return m;
	else
		return n;
}
void _0_1_knapsack(int* weight, int* price, int m_num, int w_sum){
	if (weight == NULL || price == NULL || m_num <= 0 || w_sum <= 0)
		return;
	int** m_price = (int**)malloc(sizeof(int*)*m_num);
	for (int i = 0; i < m_num; i++){
		m_price[i] = (int*)malloc(sizeof(int)*(w_sum+1));
	}
	
	for (int j = 0; j < min_fun(weight[m_num]-1,w_sum); j++){
		m_price[m_num - 1][j] = 0;
	}
	for (int j = weight[m_num-1] - 1; j < w_sum; j++){
		m_price[m_num - 1][j] = price[m_num-1];
	}
	for (int i = m_num - 1; i > 1; i--){
		for (int j = 0; j < min_fun(weight[i]-1, w_sum); j++)
		{
			m_price[i][j] = m_price[i + 1][j];
		}
		for (int j = weight[i]; j < w_sum; j++){
			m_price[i][j] = max_fun(m_price[i + 1][j], m_price[i + 1][j - weight[i]] + price[i]);
		}
	}
	if (w_sum < weight[0])
		m_price[0][w_sum - 1] = m_price[1][w_sum - 1];
	else
		m_price[0][w_sum - 1] = max_fun(m_price[1][w_sum - 1], m_price[1][w_sum - 1] + price[0]);
	for (int i = 0; i < m_num; i++){
		free(m_price[i]);
	}
	free(m_price);
}