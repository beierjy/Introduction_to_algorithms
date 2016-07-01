//迭代的FFT，比递归的运行更快
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#define pi 3.1415926535 
struct Complex
{
    double imag;
	double real;
	Complex(double r=0,double i=0){imag=i,real=r;}
};
vector<Complex>a;
Complex operator* (Complex const & lhs, Complex const & rhs)
{
	Complex temp;
	temp.real = lhs.real * rhs.real - lhs.imag * rhs.imag;
	temp.imag= lhs.real * rhs.imag + lhs.imag * rhs.real;
	return temp;
}
Complex operator+ (Complex const & lhs, Complex const & rhs)
{
	Complex temp;
	temp.real =lhs.real+rhs.real;
	temp.imag = lhs.imag+ rhs.imag;
	return temp;
}
Complex operator- (Complex const & lhs, Complex const & rhs)
{
	Complex temp;
	temp.real = lhs.real - rhs.real;
	temp.imag = lhs.imag - rhs.imag;
	return temp;
}
int rev(int k)
{
	int temp=0,i=0;
	static int flag=0;
	size_t n=a.size()-1;
	if (!flag){while(n>>i)i++;flag=i;}//设置哨兵为了只调用一次这个循环
	int j=flag;
	vector<int>b(n+1,0);
	while (j>0)
	{
		//b[--j]=(k-((k>>1)<<1));
		b[--j]=k%2;
		k>>=1;
		temp+=b[j]<<j;
	}
	return temp;
}
vector<Complex> BIT_REVERSE_COPY(vector<Complex>&a,vector<Complex>&A)
{
	size_t n=a.size();
    for (size_t k=0;k<n;k++)
    {
		A[rev(k)]=a[k];
    }
	return A;
}
int Log(int n)//由于n是2的幂，所以函数返回值一定是整数
{
     int temp=0;
     while (n>>=1) temp++;
	 return temp;
}
vector<Complex> ITERATIVE_FFT(vector<Complex>&a,vector<Complex>&A)
{
    BIT_REVERSE_COPY(a,A);
	size_t n=a.size();
	for (int s=1;s<=Log(n);s++)
	{
		int m=pow(2,s);
		for (int k=0;k<=n-1;k+=m)
		{
			Complex w(1,0),wm(cos(2*pi/m),sin(2*pi/m)),t,u;
			for (int j=0;j<=m/2-1;j++)
			{
                t=w*A[k+j+m/2];
				u=A[k+j];
				A[k+j]=u+t;
				A[k+j+m/2]=u-t;
				w=w*wm;
			}
		}
	}
	return A;
}
void main()
{
	 Complex x,y;
	 int i=0;
	 while (cin>>x.real>>x.imag)//输入复系数
	 {
		 a.push_back(x);
		 i++;
	 }
	 vector<Complex>A(i,y);
	 BIT_REVERSE_COPY(a,A);
	 vector<Complex>yy = ITERATIVE_FFT(a,A);
	 for (int t = 0; t<A.size(); t++)
	 {
		 printf("%g", A[t].real);//求DFT逆需要把结果÷n
		 if (fabs(A[t].imag) < 0.001)//虚数小于0.001，那么虚数忽略不计
		 {
			 cout << endl;
			 continue;
		 }
		 else
		 {
			 if (A[t].imag<0) printf("%gi", A[t].imag);
			 else printf("+%gi", A[t].imag);
		 }
		 cout << endl;
	}
}