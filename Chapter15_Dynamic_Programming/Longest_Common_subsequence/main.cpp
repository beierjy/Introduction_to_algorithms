#include "LCS.h"

typedef char Type;
int main(){
	char X[7] = { 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	char Y[6] = { 'B', 'D', 'C', 'A', 'B', 'A' };
	LCS_length(X, Y, 7, 6);

	system("pause");
	return 0;
}