#include "Huffman.h"

int main(){
	code a[6] = { code(5, 'f'), code(9, 'e'), code(12, 'c'), code(13, 'b'), code(16, 'd'), code(45, 'a') };
	Huffman(a, 6);
	system("pause");
	return 0;
}