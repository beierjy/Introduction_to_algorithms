//矩阵类
#ifndef MATRIX_H
#define MATRIX_H
template <class Type>
class Matrix
{
public:
	template <typename Type>//必须加上类型说明
	friend void square_matrix_multiply(const Matrix<Type> &m1, const Matrix<Type> &m2,Matrix<Type> &m3);//必须与下面的定义一样的形势，并且局部变量是不能返回出来的。
	template <typename Type>
	friend void square_matrix_multiply_recursive(Matrix<Type> &A, Matrix<Type> &B, Matrix<Type> &C);
	template <typename Type>
	friend Matrix<Type> operator +(const Matrix<Type> &m1, const Matrix<Type> &m2);
	template <typename Type>
	friend Matrix<Type> operator -(const Matrix<Type> &m1, const Matrix<Type> &m2);
	template <typename Type,typename T>
	friend Matrix<Type> operator *(const Matrix<Type> &m1, T k);
	template <typename Type, typename T>
	friend Matrix<Type> operator /(const Matrix<Type> &m1, T k);
	template <typename Type>
	friend Matrix<Type> FourMerge(Matrix<Type> &mat1, Matrix<Type> &mat2, Matrix<Type> &mat3, Matrix<Type> &mat4);
	template <typename Type>
	friend void Strassen(Matrix<Type> &A, Matrix<Type> &B, Matrix<Type> &C);
public:
	Matrix(size_t r = 0, size_t c = 0);
	Matrix(Type **a, const size_t r, const size_t c);
	Matrix(const Matrix &m);
	Matrix<Type>& operator= (const Matrix &m);
	Matrix<Type>& divide(size_t r1, size_t c1, size_t r2, size_t c2);
	void FourPartsDivideMatrix(Matrix &mat1, Matrix &mat2, Matrix &mat3, Matrix &mat4);
	void printMat();
	~Matrix();
private:
	size_t row, col;
	Type** mat;
};
//#include "Matrix.cpp"
#endif