#include"0_1_knapsack.h"


int main(){
	int weight[3] = { 10, 20, 30 };
	int price[3] = { 101, 100, 120 };
	//recur_0_1_knapsack(weight, price, 3, 40);
	_0_1_knapsack(weight, price, 3, 20);
	system("pause");
	return 0;
}