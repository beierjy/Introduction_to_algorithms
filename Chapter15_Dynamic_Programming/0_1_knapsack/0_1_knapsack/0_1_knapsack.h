//Chapter15 Dynamic algorithm
//0_1 knapsack problem 

#include <stdio.h>
#include <stdlib.h>

//递归求解
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
	printf("%d\n", max);
	free(sum_price);
}

//上述遍历，必须用递归进行求子结构的最小值，否则是错误的
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
//weight 表示每件物品的重量，price表示没见物品的价值，m_num表示总共有多少件物品，w_sum表示背包总共可以有多少件物品
int _0_1_knapsack(int* weight, int* price, int m_num, int w_sum){
	if (weight == NULL || price == NULL || m_num <= 0 || w_sum <= 0)
		return 0;
	int** m_price = (int**)malloc(sizeof(int*)*(m_num));
	for (int i = 0; i < m_num; i++){
		m_price[i] = (int*)malloc(sizeof(int)*(w_sum+1));
	}
	for (int i = 0; i < m_num; i++){
		for (int j = 0; j <= w_sum; j++){
			m_price[i][j] = 0;
		}
	}
	//初始化最后一行，在小于zui后一个重量的时候最后一行全部初始化为0.
	for (int j = 0; j <= min_fun(weight[m_num-1]-1,w_sum); j++){
		m_price[m_num - 1][j] = 0;
	}
	//初始化最后一行，在大于最后一件物品之后的所有物品全部都初始化为最后一件物品的价值
	for (int j = weight[m_num-1]; j <= w_sum; j++){
		m_price[m_num - 1][j] = price[m_num-1];
	}
	for (int i = m_num - 2; i > 0; i--){
		for (int j = 0; j <= min_fun(weight[i]-1, w_sum); j++)
		{
			m_price[i][j] = m_price[i + 1][j];//在为到达第i个物品质量之前，直接更新前面的m_price;
		}
		//这里便是从减去新加入的质量的下层往上计算,在到达第i个时候，比较哪个大，如果打的话，则加入
		for (int j = weight[i]; j <= w_sum; j++){
			m_price[i][j] = max_fun(m_price[i + 1][j], m_price[i + 1][j - weight[i]] + price[i]);
		}
	}
	if (w_sum < weight[0]){
		m_price[0][w_sum] = m_price[1][w_sum];
	}
	else{
		m_price[0][w_sum] = max_fun(m_price[1][w_sum], m_price[1][w_sum - weight[0]] + price[0]);
	}
	for (int i = 0; i < m_num; i++){
		for (int j = 0; j <= w_sum; j++)
			printf("%d ", m_price[i][j]);
		printf("\n");
	}
	int max = m_price[0][w_sum];
	for (int i = 0; i < m_num; i++){
		free(m_price[i]);
	}
	free(m_price);
	return max;
}
