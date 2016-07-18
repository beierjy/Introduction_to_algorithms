#include "KMP.h"

int main(){
	char a[9] = { 'a', 'b', 'a', 'c', 'b', 'c','d','h','i' };
	char b[4] = { 'c', 'b', 'c','d' };
	//int s = naive_string_match(a, b, 6, 3);
	int x = kmp_matcher(a, b, 9, 4);
	printf("\n %d", x);
	//printf("%d\n", s);
	system("pause");
	return 0;
}
