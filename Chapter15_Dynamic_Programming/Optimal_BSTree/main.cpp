#include "Optimal_BSTree.h"
typedef char Type;
int  main(){
	Type ch[5] = { '1', '2', '3', '4', '5' };
	float p_in[6] = { 0.0,0.15, 0.10, 0.05, 0.10, 0.20 };
	float p_out[6] = { 0.05, 0.10, 0.05, 0.05, 0.05,0.10 };
	Optimal_BSTree(ch, p_in, p_out, 5);
	system("pause");
	return 0;
}