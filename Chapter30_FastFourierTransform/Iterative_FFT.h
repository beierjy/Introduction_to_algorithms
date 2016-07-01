#include <iostream>
#include <cmath>
#include <complex>

#define PI 3.14159265
using namespace std;

int rev(int k,int n)
{
	int temp = 0,i = 0;
	static int flag = 0;
	if(!flag)
	{
		while((n - 1) >> i)
			i++;
		flag = i;
	}
	int j = flag;
	int * b = new int[n];
	for(int iter = 0;iter < n;++iter)
	{
		b[iter] = 0;
	}
	while(j > 0)
	{
		b[--j] = k % 2;
		k >>= 1;
		temp += b[j] << j;
	}
	delete[]b;
	return temp;
}

void bit_reverse_copy(double* a,int n)
{
	double * a1 = new double[n];
	for(int i = 0;i < n;++i)
		a1[rev(i,n)] = a[i];
	for(int i = 0;i < n;++i)
		a[i] = a1[i];
	delete [] a1;
}

complex<double>* iterative_FFT(double* a,int n)
{
	complex<double>* y = new complex<double>[n];
	bit_reverse_copy(a,n);
	for(int i = 0;i < n;++i)
	{
		y[i] = complex<double>(a[i],0);
	}
	complex<double> c,wm;
	complex<double> t,u;int m;
	int temp = log10(n) / log10(2);
	for(int s = 1;s <= temp;++ s)
	{
		m = pow(2,s);
		double temp1 = 2 * PI / m;
		c = complex<double>(0,temp1);
		wm = exp(c);
		for(int k  = 0;k < n;k += m)
		{
			complex<double> w = complex<double>(1,0);
			for(int j = 0;j < m / 2; ++j)
			{
				t = w * y[k + j + m / 2];
				u = y[k + j];
				y[k + j] = u + t;
				y[k + j + m / 2] = u - t;
				w *= wm;
			}
		}
	}
	return y;
}
void bit_reverse_copy1(complex<double>* a,int n)
{
	complex<double> * a1 = new complex<double>[n];
	for(int i = 0;i < n;++i)
		a1[rev(i,n)] = a[i];
	for(int i = 0;i < n;++i)
		a[i] = a1[i];
	delete [] a1;
}
double* iterative_FFT_opposite(complex<double>* y,int n)
{
	complex<double>* a = new complex<double>[n];
	bit_reverse_copy1(y,n);
	for(int i = 0;i < n;++i)
	{
		a[i] = y[i];
	}
	complex<double> c,wm;
	complex<double> t,u;int m;
	int temp = log10(n) / log10(2);
	for(int s = 1;s <= temp;++ s)
	{
		m = pow(2,s);
		double temp1 = 2 * PI / m;
		c = complex<double>(0,temp1);
		wm = exp(-c);
		for(int k  = 0;k < n;k += m)
		{
			complex<double> w = complex<double>(1,0);
			for(int j = 0;j < m / 2; ++j)
			{
				t = w * a[k + j + m / 2];
				u = a[k + j];
				a[k + j] = u + t;
				a[k + j + m / 2] = u - t;
				w *= wm;
			}
		}
	}
	double* a1 = new double[n];
	for(int i = 0;i < n;++i)
	{
		a1[i] = real(a[i]) / n;
	}
	delete[] a;
	return a1;
}
