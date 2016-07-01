//chapter 15 dynamic programming
//longest common sequence 
#include <stdio.h>
#include <stdlib.h>

typedef char Type;
//自底向上的求最长公共子序列

int LCS_length_up(Type* X, Type* Y, int* len, char* res, int lenx, int leny){
	if (X == NULL || Y == NULL || len ==NULL || res == NULL ||lenx <= 0 || leny <= 0)
		return 0;
	for (int i = 1; i <= lenx; i++){
		for (int j = 1; j <= leny; j++){
			if (X[i-1] == Y[j-1]){
				int sum_len = len[(i - 1)*(leny + 1) + j - 1] + 1;
				len[i * (leny + 1) + j] = sum_len;
				res[i * (leny + 1) + j] = '@';
			}
			else{
				int sum_len1 = len[(i - 1)*(leny + 1) + j];
				int sum_len2 = len[i * (leny + 1) + j - 1];;
				if (sum_len1 >= sum_len2){
					len[i * (leny + 1) + j] = sum_len1;
					res[i * (leny + 1) + j] = '#';
				}
				else{
					len[i * (leny + 1) + j] = sum_len2;
					res[i * (leny + 1) + j] = '$';
					
				}
 			}
		}
	}
	return len[(lenx + 1) * (leny + 1) - 1];
}

void print_LCS(Type* X, char* res, int i, int j,int lenx,int leny){
	if (i == 0 || j == 0)
		return;
	if (res[i * (leny+ 1) + j] == '@'){
		print_LCS(X, res, i - 1, j - 1, lenx, leny);
		printf("%c ", X[i - 1]);
	}
	else if (res[i * (leny+1) + j] == '#')
		print_LCS(X, res, i - 1, j, lenx, leny);
	else
		print_LCS(X, res, i, j - 1, lenx, leny);
}

int LCS_length(Type* X, Type* Y, int lenx, int leny){
	if (X == NULL || Y == NULL || lenx <= 0 || leny <= 0)
		return 0;
	int* len = (int*)malloc(((lenx + 1)*(leny + 1))*sizeof(int));
	char* res = (char*)malloc(((lenx + 1)*(leny + 1))*sizeof(char));

	for (int i = 0; i < (lenx + 1 )*(leny + 1); i++){
		len[i] = 0;
		res[i] = '0';
	}
	int maxlen = LCS_length_up(X, Y, len, res, lenx, leny);
	for (int i = 0; i < (lenx + 1)*(leny + 1); i++){
		if (i % (leny + 1) == 0)
			printf("\n");
		printf("%d\t", len[i]);
			
	}
	printf("\n\n");
	for (int i = 0; i < (lenx + 1)*(leny + 1); i++){
		if (i % (leny + 1) == 0)
			printf("\n");
		printf("%c\t", res[i]);

	}
	print_LCS(X, res, lenx, leny, lenx, leny);
	free(len);
	free(res);
	return maxlen;
}