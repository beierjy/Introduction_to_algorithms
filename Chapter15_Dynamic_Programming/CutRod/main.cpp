#include "CutRod.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
	int p[14] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30,32, 33,34};
	int result = Cut_rod_recur(10, p);
	int result1 = Memoized_cut_rod(13, p);
	
	printf("%d\n", result);
	printf("%d\n", result1);
	print_cut_rod_solution(13, p);
	system("pause");
	return 0;
}