//定义多项式类
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

using namespace std;
class Term
{
	friend class Polynomial;
public:
	double coef;
	int exp;
};

class Polynomial
{
	friend Polynomial operator + (const Polynomial&, const Polynomial&);
	friend Polynomial operator * (const Polynomial&, const Polynomial&);
	friend ostream& operator << (ostream&, const Polynomial&);
	friend Polynomial DotMultiply(const Polynomial& p1, const Polynomial& p2);
public:
	Polynomial(int c = 0);
	Polynomial(const Polynomial&);
	Polynomial& operator = (const Polynomial&);
	~Polynomial();
	void addTerm(double c,int e);
	double Eval(double);
private:
	Term* TermArray;
	int capacity;

};
void Test();

#endif