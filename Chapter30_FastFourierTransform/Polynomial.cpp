#include "Polynomial.h"
#include <math.h>
#include <iostream>
#include <cmath>
#include "recur_FFT.h"
#include "Iterative_FFT.h"


Polynomial::Polynomial(int c)
{
	capacity = c;
	TermArray = new Term[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		TermArray[i].coef = 0;
		TermArray[i].exp = i;
	}
}

Polynomial::Polynomial(const Polynomial& p)
{
	capacity = p.capacity;
	TermArray = new Term[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		TermArray[i].coef = p.TermArray[i].coef;
		TermArray[i].exp = p.TermArray[i].exp;
	}
}

Polynomial& Polynomial::operator=(const Polynomial& p)
{
	capacity = p.capacity;
	TermArray = new Term[capacity];
	for (int i = 0; i < p.capacity; ++i)
	{
		TermArray[i].coef = p.TermArray[i].coef;
		TermArray[i].exp = p.TermArray[i].exp;
	}
	return *this;
}

Polynomial::~Polynomial()
{
	delete[] TermArray;
}

void Polynomial::addTerm(double c,int e)
{
	if (capacity > 0)
	{
		if (e > TermArray[capacity - 1].exp)
		{
			Term* newTerm = new Term[e + 1];
			int i = 0;
			for (; i < capacity; ++i)
			{
				newTerm[i] = TermArray[i];
			}
			for (int j = i; j < e; j++)
			{
				newTerm[j].coef = 0;
				newTerm[j].exp = j;
			}
			newTerm[e].coef = c;
			newTerm[e].exp = e;
			capacity = e + 1;
			delete[] TermArray;
			TermArray = newTerm;
		}
		else
		{
				TermArray[e].coef += c;
				TermArray[e].exp = e;
		}
	}
	else
	{
		Term* newTerm = new Term[e + 1];
		int i = 0;
		for (; i < e; ++i)
		{
			newTerm[i].coef = 0;
			newTerm[i].exp = i;
		}
		newTerm[e].coef = c;
		newTerm[e].exp = e;
		capacity = e + 1;
		TermArray = newTerm;
	}
}
double Polynomial::Eval(double x)
{
	double result = 0;
	for (int i = 0; i < capacity - 1; ++i)
	{
		double tmp = 1; double temp = 0;
		if (TermArray[i].coef != 0)
		{
			for (int j = 1; j <= TermArray[i].exp; ++j)
				tmp *= x;
		}
		result += TermArray[i].coef * tmp;
	}
	
	return result;
}

Polynomial operator + (const Polynomial& p1, const Polynomial& p2)
{
	int max;
	if (p1.capacity >= p2.capacity)
		max = p1.capacity;
	else
		max = p2.capacity;
	Polynomial p3(max);
	int i = 0;
	if (p1.capacity < p2.capacity)
	{
		for (; i < p1.capacity; ++i)
			p3.TermArray[i].coef = p1.TermArray[i].coef + p2.TermArray[i].coef;
		while (i < max)
		{
			p3.TermArray[i].coef = p2.TermArray[i].coef;
			++i;
		}
	}
	else if (p1.capacity >= p2.capacity)
	{
		for (; i < p2.capacity; ++i)
			p3.TermArray[i].coef = p1.TermArray[i].coef + p2.TermArray[i].coef;
		while (i < max)
		{
			p3.TermArray[i].coef = p1.TermArray[i].coef;
			++i;
		}
	}
	return p3;
}
ostream& operator << (ostream& out, const Polynomial& p)
{
	cout << "f(x) = ";
	if (p.capacity > 0)
	{
		int i = 0;
		for (; i < p.capacity - 1; ++i)
		{
			if (p.TermArray[i].coef != 0)
			{
				out << p.TermArray[i].coef << " * " << "x ^ " << p.TermArray[i].exp;
				if (i + 1 < p.capacity || p.TermArray[i + 1].coef != 0)
				{
					out << " + ";
				}
			}
		}
		if (p.TermArray[p.capacity - 1].coef != 0)
			out<< p.TermArray[p.capacity - 1].coef << " * " << "x ^ " << p.TermArray[p.capacity - 1].exp;
		out << endl;
	}
	else
		out << 0;
		
	return out;
}
Polynomial operator * (const Polynomial &p1, const Polynomial &p2)
{
	Polynomial p3(p1.capacity + p2.capacity - 1);
	for (int i = 0; i < p1.capacity; ++i)
	{
		for (int j = 0; j < p2.capacity; ++j)
			p3.addTerm(p1.TermArray[i].coef * p2.TermArray[j].coef, i + j);
	}
	return p3;
}

Polynomial DotMultiply(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial p3(p1.capacity + p2.capacity - 1);
	complex<double> c = complex<double>(0, 2 * PI / (2 * p1.capacity));
	complex<double> wn = exp(c);
	double *a1 = new double[2 * p1.capacity];
	double *a2 = new double[2 * p2.capacity];
	for (int i = 0; i < p1.capacity; ++i)
		a1[i] = p1.TermArray[i].coef;
	for (int i = p1.capacity; i < 2 * p1.capacity; ++i)
		a1[i] = 0.0;
	for (int i = 0; i < p2.capacity; ++i)
	{
		a2[i] = p2.TermArray[i].coef;
	}
	for (int i = p2.capacity; i < 2 * p2.capacity; ++i)
		a2[i] = 0.0;
	
	complex<double>* y1 = new complex<double>[2 * p1.capacity];
	complex<double>* y2 = new complex<double>[2 * p2.capacity];
	complex<double>* y3 = new complex<double>[p1.capacity + p2.capacity];
	y1 = recursive_FFT(a1, 2 * p1.capacity);
	y2 = recursive_FFT(a2, 2 * p2.capacity);

	/*y1 = iterative_FFT(a1, 2 * p1.capacity);
	y2 = iterative_FFT(a2, 2 * p2.capacity);*/

	for (int k = 0; k < 2 * p1.capacity; ++k)
		y3[k] = y1[k] * y2[k];
	double *a = new double[p1.capacity + p2.capacity];
	a = FFT_opposite(y3,p1.capacity + p2.capacity );
	for (int i = 0; i < p1.capacity + p2.capacity - 1 ; ++i)
		p3.addTerm(a[i], i);
	return p3;
}
void Test()
{
	//调试DFT和DFT反变换使用
	double a[] = {1,2,3,4,5,6,7,8};
	int n = 8;
	complex<double>* y;
	y = recursive_FFT(a,n);
	for(int i = 0;i < n;++i)
		cout<<y[i]<<" ";
	cout<<endl;
	complex<double>* y1;
	y1 = iterative_FFT(a,n);
	cout<<endl;
	for(int i = 0;i < n;++i)
		cout<<y1[i]<<" ";

	cout<<endl;
	double* b;
	b =  iterative_FFT_opposite(y,n);
	for(int i = 0;i < n;++i)
		cout<<b[i]<<" ";
	Polynomial p1;
	p1.addTerm(1, 0);
	p1.addTerm(2, 1);
	p1.addTerm(3, 2);
	p1.addTerm(4, 3);
	//cout << p1 << endl;
	Polynomial p2(p1);

	Polynomial p3 = p2;
	
	Polynomial p6;
	cout << "\n****" << endl;
	p6 = DotMultiply(p2, p3);
	cout << p6 << endl;
	cout<<endl<<endl;
	p6 = p2 * p3;
	cout << p6 << endl;
	cout << "\n*****" << endl;
	p3.addTerm(5.2, 3);
	p3.addTerm(5.2, 6);
	p3.addTerm(5.2, 10);
	p3.addTerm(5.2, 7);
	cout << p3 << endl;
	cout << p2.Eval(2.34) << endl;
	Polynomial p4;
	p4 = p2 + p3;
	Polynomial p5;
	p5 = p1 * p2;
	cout << p4 << endl;
	cout << p5 << endl;
	cout << p4.Eval(2.34) << endl;
}