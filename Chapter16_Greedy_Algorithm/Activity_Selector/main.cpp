#include "activity_selector.h"

int main(){
	int start[12] = { 0,1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	int finish[12] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };
	selector(start, finish, 11);
	system("pause");
	return 0;
}