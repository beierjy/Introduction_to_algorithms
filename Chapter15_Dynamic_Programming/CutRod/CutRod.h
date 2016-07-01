// Introduction to Algorithms chapter 15
#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
//动态规划，时间复杂度为（2^n），
int Cut_rod_recur(int length,int* price){
	if (length <= 0)
		return 0;
	int sum_price = INT_MIN;
	int sub_price = 0;
	for (int i = 1; i <= length; i++){
		sub_price = Cut_rod_recur(length - i, price);
		sum_price = (sum_price >= (price[i] + sub_price) ? sum_price : (price[i] + sub_price));
	}
	return sum_price;
}
//带备忘录的自顶向下的动态规划解决钢条分割问题
int memoized_cut_rod_AUX(int length,int* price,int* r){
	if (r[length] >= 0)
		return r[length];
	int sum_price = 0;
	if (length == 0)
		sum_price = 0;
	else
		sum_price = INT_MIN;
	int sub_price = 0;
	for (int i = 1; i <= length; i++){
		sub_price = memoized_cut_rod_AUX(length - i, price,r);
		sum_price = (sum_price >= (price[i] + sub_price) ? sum_price : (price[i] + sub_price));
	}
	r[length] = sum_price;
	return sum_price;
}
int Memoized_cut_rod(int length, int* price){
	if (length <= 0)
		return 0;
	int* r = (int*)malloc(sizeof(int)*(length + 1));
	for (int i = 0; i <= length; i++){
		r[i] = INT_MIN;
	}
	int sum_price = memoized_cut_rod_AUX(length, price, r);
	free(r);
	return sum_price;
}

//自底向上的解决钢条分割
int Bottom_up_cut_rod(int length, int* price,int* r,int* s){
	if (length <= 0)
		return 0;
	int sum_price;
	for (int i = 1; i <= length; i++){
		sum_price = INT_MIN;
		for (int j = 1; j <= i; j++){
			//sum_price = (sum_price >= (price[j] + r[i - j])) ? sum_price : (price[j] + r[i - j]);
			if (sum_price < price[j] + r[i - j])
			{
				sum_price = price[j] + r[i - j];
				s[i] = j;
			}
		}
		r[i] = sum_price;
	}
	sum_price = r[length];
	
	
	return sum_price;
}
void print_cut_rod_solution(int length, int* price){
	int* r = (int*)malloc(sizeof(int)*(length + 1));
	int* s = (int*)malloc(sizeof(int)*(length + 1));
	for (int i = 0; i <= length; i++){
		r[i] = 0;
	}
	Bottom_up_cut_rod(length, price, r, s);
	printf("%d : ", r[length]);
	while (length > 0){
		printf("%d ", s[length]);
		length = length - s[length];
	}
	
	free(r); free(s);
}