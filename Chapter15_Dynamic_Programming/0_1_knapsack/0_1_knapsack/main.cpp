#include"0_1_knapsack.h"


int main(){
	int weight[3] = { 10, 20, 30 };
	int price[3] = { 60, 100, 120 };
	//recur_0_1_knapsack(weight, price, 3, 50);
	_0_1_knapsack_1(weight, price, 3, 50);
	system("pause");
	return 0;
}