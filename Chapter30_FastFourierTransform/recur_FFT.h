#include <iostream>
#include <complex>
#include <cmath>

#define PI 3.14159265
using namespace std;

//�����n����λ�����ĵ�ֵ�������n������2��������
complex<double>* recursive_FFT(double* a,int n)
{
	complex<double>* y = new complex<double>[n];
	if (n == 1)
	{
		//���� return &complex<double>(a[0], 0)
		complex<double> *p = new complex<double>(a[0], 0);//����ǲ�����ֱ��ȡ��ַ���صģ�
		return p;
	}
	complex<double> c = complex<double>(0, 2 * PI / n);
	complex<double> wn = exp(c);
	complex<double> w = complex<double>(1,0);
	double *a0 = new double[n / 2];
	double *a1 = new double[n / 2];
	for (int i = 0; i < n; i = i + 2)
	{
		a0[i / 2] = a[i];
	}
	for (int i = 1; i < n; i = i + 2)
	{
		a1[(i - 1) / 2] = a[i];
	}
	complex<double>* y0 = recursive_FFT(a0, n / 2);//����ִ����DFT(n/2)��
	complex<double>* y1 = recursive_FFT(a1, n / 2);
	
	complex<double> temp;
	for (int k = 0; k < n / 2; ++k)
	{
		temp = w * y1[k];
		y[k] = y0[k] + temp;
		y[k + n / 2] = y0[k] - temp;
		w *= wn;
	}	
	
	delete[] a0;
	delete[] a1;
	return y;	
}
complex<double> *recursive_FFT_opposite(complex<double>* y,int n)
{
	complex<double>* a = new complex<double>[n];
	if (n == 1)
	{
		return y;
	}
	complex<double> c = complex<double>(0, -2 * PI / n);
	complex<double> wn = exp(c);
	complex<double> w = complex<double>(1,0);
	complex<double> *y0 = new complex<double>[n / 2];
	complex<double> *y1 = new complex<double>[n / 2];
	for (int i = 0; i < n; i = i + 2)
	{
		y0[i / 2] = y[i];
	}
	for (int i = 1; i < n; i = i + 2)
	{
		y1[(i - 1) / 2] = y[i];
	}
	complex<double>* a0 = recursive_FFT_opposite(y0, n / 2);
	complex<double>* a1 = recursive_FFT_opposite(y1, n / 2);
	complex<double> temp;
	for (int k = 0; k < n / 2; ++k)
	{
		temp = w * a1[k];
		a[k] = a0[k] + temp;
		a[k + n / 2] = a0[k] - temp;
		w *= wn;
	}	
	delete[] y0;
	delete[] y1;
	return a;	
}
double* FFT_opposite(complex<double>* y,int n)
{
	complex<double>* a1 = recursive_FFT_opposite(y,n);
	double* a = new double[n];
	for(int i = 0;i < n;++i)
	{
		a[i] = real(a1[i]) / n;
	}
	return a;
}




	