//Chapter32 String Match algorithm
//KnuthMorrisPratt

#include <stdlib.h>
#include <stdio.h>

//���ص��ַ���ƥ���㷨
int naive_string_match(char* Template, char* Pstring, int m_t, int m_p){
	if (Template == NULL || Pstring == NULL || m_t < 0 || m_p < 0)
		return -1;
	int i = 0;
	while (i < m_t){
		char c_tmp = Template[i];
		int tmp_i = i;
		if (c_tmp == Pstring[0]){
			bool tag = false;
			for (int j = 0; j < m_p; j++){
				if (c_tmp == Template[i + 1] && tag == false){
					tag = true;
					tmp_i = i + 1;//�����ͬ���ַ��������Ƴ٣�
				}
				if (Template[i] == Pstring[j] && i <= m_t&&j < m_p){
					i++;
				}
				else if (Template[i] != Pstring[j] || i >= m_t || j >= m_p){
					i = tmp_i;
					break;
				}
				if (j == (m_p - 1) && Template[i - 1] == Pstring[j]){
					return i - j;
					break;
				}
			}
		}
		else
			i++;
	}
	return -1;
}

//KMP 
//��next����
void getnext(char* pattern, int m_num, int* next){
	if (pattern == NULL || m_num < 0 || next == NULL)
		return;
	next[0] = -1;
	int i = 0;
	int j = -1;
	while (i < m_num){
		if (j == next[0] || pattern[j] == pattern[i]){
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

int kmp_matcher(char* temp, char* pattern, int m_t, int m_p){
	if (temp == NULL || pattern == NULL || m_t < 0 || m_p < 0)
		return -1;
	int *next = (int*)malloc(sizeof(int)*m_p);
	for (int k = 0; k < m_p; ++k){
		next[k] = 0;
	}
	getnext(pattern, m_p, next);
	for (int k = 0; k < m_p; ++k){
		printf("%d\t", next[k]);
	}
	int i = 0;//������λ��
	int j = 0;// ģʽ����λ��
	while (i < m_t && j < m_p){
		if (j == -1 || temp[i] == pattern[j]){
			i++;
			j++;
		}
		else
			j = next[j];//j �ص�ָ����λ��
	}
	if (j == m_p)
	{
		return i - j;
	}
	else
		return -1;
}


