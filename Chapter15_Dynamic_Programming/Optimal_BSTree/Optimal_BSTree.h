//Chapter 15 daynamic Programming
//Optimal Binary Search Tree

#include <stdlib.h>
#include <stdio.h>
#include <limits>

typedef char Type;

int Optimal_BSTree_up(Type* ch,float* p_in,float* p_out,int m_num,float*  e_pri,float* w_pri,int* root){
	if (ch == NULL || p_in == NULL || p_out == NULL || m_num <= 0 || e_pri == NULL ||w_pri == NULL|| root == NULL)
		return 0;
	for (int i = 1; i <= m_num + 1; i++){
		e_pri[i * (m_num + 1) + i - 1] = p_out[i - 1];
		w_pri[i * (m_num + 1) + i - 1] = p_out[i - 1];
	}
	
	for (int l = 1; l <= m_num; l++){
		for (int i = 1; i <= m_num - l + 1; i++){
			int j = i + l - 1;
			e_pri[i *(m_num + 1) + j] = INT_MAX;
			w_pri[i *(m_num + 1) + j] = w_pri[i *(m_num + 1) + j - 1] + p_in[j] + p_out[j];
			for (int k = i; k <= j; k++){
				float sum_pri = e_pri[i*(m_num + 1) + k - 1] + e_pri[(k+1)*(m_num + 1) + j] + w_pri[i*(m_num + 1) + j];
				if ((sum_pri -(e_pri[i *(m_num + 1) + j]) )< 0.00001){
					e_pri[i *(m_num + 1) + j] = sum_pri;
					root[i*(m_num + 1) + j] = k;
				}
			}
		}
	}
	
	return e_pri[(m_num + 2) *(m_num + 1) - 1];
}
int Optimal_BSTree(Type* ch, float* p_in, float* p_out, int m_num){
	if (ch == NULL || p_in == NULL || p_out == NULL || m_num <= 0)
		return 0;
	float* e_pri = (float*)malloc(sizeof(float)*((m_num + 2) *(m_num + 1)));
	float* w_pri = (float*)malloc(sizeof(float)*((m_num + 2) *(m_num + 1)));
	int* root = (int*)malloc(sizeof(int)*((m_num + 2) *(m_num + 1)));
	for (int i = 0; i <((m_num + 2) *(m_num + 1)); i++){
		e_pri[i] = 0.0;
		w_pri[i] = 0.0;
		root[i] = 0;
	}
	int min = Optimal_BSTree_up(ch, p_in, p_out, m_num, e_pri, w_pri, root);
	for (int i = 0; i <((m_num + 2) *(m_num + 1)); i++){
		if (i % (m_num+1) == 0)
			printf("\n");
		printf("%f ",e_pri[i]);
	}
	printf("\n");
	for (int i = 0; i <((m_num + 2) *(m_num + 1)); i++){
		if (i % (m_num+1) == 0)
			printf("\n");
		printf("%f ", w_pri[i]);
	}
	printf("\n");
	for (int i = 0; i <((m_num + 2) *(m_num + 1)); i++){
		if (i % (m_num+1) == 0)
			printf("\n");
		printf("%d ", root[i]);
	}
	printf("\n");
	free(w_pri);
	free(e_pri);
	free(root);
	return min;
}