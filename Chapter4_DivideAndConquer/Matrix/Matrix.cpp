//当模板类与实现相分离的时候，调用时候应该包含.cpp文件
#include "Matrix.h"
#include <iostream>

using namespace std;

template <typename Type>
Matrix<Type>::Matrix(size_t r, size_t c) :row(r), col(c)
{
	mat = new Type*[row];
	for (size_t i = 0; i < row; ++i)
		mat[i] = new Type[col];


	for (size_t i = 0; i < row; ++i)
	{
		for (size_t j = 0; j < col; ++j)
			mat[i][j] = 0;
	}
}
template <typename Type>
Matrix<Type>::Matrix(const Matrix &m) :row(m.row), col(m.col)
{
	mat = new Type*[row];
	for (size_t i = 0; i < row; ++i)
		mat[i] = new Type[col];
	for (size_t i = 0; i < m.row; ++i)
	{
		for (size_t j = 0; j < m.col; ++j)
			mat[i][j] = m.mat[i][j];
	}
}

template <typename Type>
Matrix<Type>& Matrix<Type>::divide(size_t r1, size_t c1, size_t r2, size_t c2)
{
	Type** M = new Type*[r2 - r1];
	for (size_t i = r1; i < r2; ++i)
		M[i] = new Type[c2 - c1];
	for (size_t i = r1; i < r2; ++i)
		for (size_t j = c1; j < c2; ++j)
			M[i][j] = mat[i][j];
	mat = M;
	row = r2 - r1;
	col = c2 - c1;
	return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator= (const Matrix &m)
{
	row = m.row;
	col = m.col;
	Type** M = new Type*[m.row];
	for (size_t i = 0; i < m.row; ++i)
		M[i] = new Type[m.col];
	for (size_t i = 0; i < m.row; ++i)
		for (size_t j = 0; j < m.col; ++j)
			M[i][j] = m.mat[i][j];
	mat = M;
	return *this;
}

template <typename Type>
void Matrix<Type>::FourPartsDivideMatrix(Matrix &mat1, Matrix &mat2, Matrix &mat3, Matrix &mat4)
{
	if (row == col && row % 2 == 0)
	{
		size_t n = row / 2;
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				mat1.mat[i][j] = mat[i][j];
		for (size_t i = 0; i < n; ++i)
			for (size_t j = n; j < col; ++j)
				mat2.mat[i][j - n] = mat[i][j];
		for (size_t i = n; i < row; ++i)
			for (size_t j = 0; j < n; ++j)
				mat3.mat[i - n][j] = mat[i][j];
		for (size_t i = n; i < row; ++i)
			for (size_t j = n; j < col; ++j)
				mat4.mat[i - n][j - n] = mat[i][j];
	}

}

template <typename Type>
void Matrix<Type>::printMat()
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

template <typename Type>
Matrix<Type>::~Matrix()
{
	for (size_t i = 0; i < row; i++)
	{

		delete[]mat[i];
		//cout << "exec3" << i << endl;
	}
	delete[]mat;
}

template <typename Type>
Matrix<Type>::Matrix(Type **a, const size_t r, const size_t c) :row(r), col(c)
{
	mat = new Type*[row];
	for (size_t i = 0; i < row; ++i)
		mat[i] = new Type[col];
	for (size_t i = 0; i < r; ++i)
	{
		for (size_t j = 0; j < c; ++j)
		{
			mat[i][j] = *((int *)a + i*col + j);
			//mat[i][j] = *(a + i*col + j);//这里如果a转变成了指针之后就不能用下标的那样输出来，然后动态分配的空间不一定是连续的，所以不能那么直接相加使用
			//cout << "{ " << i << "," << j << " }"  << " " << mat[i][j] << endl;
		}

	}
}

template <typename Type>
Matrix<Type> operator+(const Matrix<Type> &m1, const Matrix<Type> &m2)
{
	Matrix<Type> m3(m1.row, m1.col);
	for (size_t i = 0; i < m1.row; ++i)
		for (size_t j = 0; j < m1.col; ++j)
			m3.mat[i][j] = m1.mat[i][j] + m2.mat[i][j];
	return m3;
}

template <typename Type>
Matrix<Type> operator-(const Matrix<Type> &m1, const Matrix<Type> &m2)
{
	Matrix<Type> m3(m1.row, m1.col);
	for (size_t i = 0; i < m1.row; ++i)
		for (size_t j = 0; j < m1.col; ++j)
			m3.mat[i][j] = m1.mat[i][j] - m2.mat[i][j];
	return m3;
}
template <typename Type>
Matrix<Type> FourMerge(Matrix<Type> &m1, Matrix<Type> &m2, Matrix<Type> &m3, Matrix<Type> &m4)
{
	if (m1.row != m2.row || m1.col != m2.col || m1.row != m3.row || m1.col != m3.col || m1.row != m4.row || m1.col != m4.col)
	{
		throw runtime_error("cannot merge the diffirent rows matrix!");
	}
	Matrix<Type> m5(m1.row + m3.row, m1.col + m2.col);
	for (size_t i = 0; i < m1.row + m3.row; ++i)
		for (size_t j = 0; j < m1.col + m2.col; ++j)
		{
			if (i < m1.row && j < m1.col)
				m5.mat[i][j] = m1.mat[i][j];
			else if (i < m1.row && j >= m1.col)
				m5.mat[i][j] = m2.mat[i][j - m1.col];
			else if (i >= m1.row && j < m1.col)
				m5.mat[i][j] = m3.mat[i - m1.row][j];
			else
				m5.mat[i][j] = m4.mat[i - m1.row][j - m1.col];
		}
	return m5;
}

//直接求矩阵的乘法时间复杂度为O（n^3)；
template <typename Type>
void square_matrix_multiply(const Matrix<Type> &m1, const Matrix<Type> &m2, Matrix<Type> &m3)
{
	if (m1.col != m2.row)
	{
		throw runtime_error("The two matrix cannot be multiplied");
	}
	for (size_t i = 0; i < m1.row; ++i)
	{
		for (size_t j = 0; j < m2.col; ++j)
		{
			m3.mat[i][j] = 0;
			for (size_t k = 0; k < m1.col; ++k)
			{
				m3.mat[i][j] = m3.mat[i][j] + m1.mat[i][k] * m2.mat[k][j];
			}
		}
	}
}

//普通分治法求矩阵的乘法,时间复杂度为8T(n/2)+ O(n^2)主方法求得为O(n^3)；
template <typename Type>
void square_matrix_multiply_recursive(Matrix<Type> &A, Matrix<Type> &B, Matrix<Type> &C)
{
	if (A.row != A.col && B.row != B.col && A.row != B.row)
	{
		throw runtime_error("can not been computed by sequare_multiply_recursive");
	}
	if (A.row % 2 != 0)
		square_matrix_multiply(A, B, C);
	else
	{
		size_t n = A.row;
		if (n == 1)
			C.mat[0][0] = A.mat[0][0] * B.mat[0][0];
		else
		{
			n = n / 2;
			Matrix<Type> A11(n, n), A12(n, n), A21(n, n), A22(n, n);
			Matrix<Type> B11(n, n), B12(n, n), B21(n, n), B22(n, n);
			Matrix<Type> C11(n, n), C12(n, n), C21(n, n), C22(n, n);
			Matrix<Type> C_11(n, n), C_12(n, n), C_21(n, n), C_22(n, n);
			A.FourPartsDivideMatrix(A11, A12, A21, A22);
			B.FourPartsDivideMatrix(B11, B12, B21, B22);
			square_matrix_multiply_recursive(A11, B11, C11);
			square_matrix_multiply_recursive(A12, B21, C_11);
			square_matrix_multiply_recursive(A21, B12, C22);
			square_matrix_multiply_recursive(A22, B22, C_22);
			square_matrix_multiply_recursive(A11, B12, C12);
			square_matrix_multiply_recursive(A12, B22, C_12);
			square_matrix_multiply_recursive(A21, B11, C21);
			square_matrix_multiply_recursive(A22, B21, C_21);
			C11 = C11 + C_11;
			C12 = C12 + C_12;
			C21 = C21 + C_21;
			C22 = C22 + C_22;
			C = FourMerge(C11, C12, C21, C22);
		}
	}
}

//Strassen方法求解矩阵乘法，时间复杂度近似为O(n^lg7)~O(n^2.81)
template <typename Type>
void Strassen(Matrix<Type> &A, Matrix<Type> &B, Matrix<Type> &C)
{
	if (A.row != A.col && B.row != B.col && A.row != B.row)
	{
		throw runtime_error("can not been computed by sequare_multiply_recursive");
	}
	if (A.row % 2 != 0)
		square_matrix_multiply(A, B, C);
	else
	{
		size_t n = A.row;
		if (n == 1)
			C.mat[0][0] = A.mat[0][0] * B.mat[0][0];
		else
		{
			n = n / 2;
			Matrix<Type> A11(n, n), A12(n, n), A21(n, n), A22(n, n);
			Matrix<Type> B11(n, n), B12(n, n), B21(n, n), B22(n, n);
			Matrix<Type> C11(n, n), C12(n, n), C21(n, n), C22(n, n);
			Matrix<Type> S1(n, n), S2(n, n), S3(n, n), S4(n, n), S5(n, n);
			Matrix<Type> S6(n, n), S7(n, n), S8(n, n), S9(n, n), S10(n, n);
			Matrix<Type> P1(n, n), P2(n, n), P3(n, n), P4(n, n), P5(n, n);
			Matrix<Type> P6(n, n), P7(n, n);
			A.FourPartsDivideMatrix(A11, A12, A21, A22);
			B.FourPartsDivideMatrix(B11, B12, B21, B22);
			S1 = B12 - B22; S2 = A11 + A12; S3 = A21 + A22; S4 = B21 - B11;
			S5 = A11 + A22; S6 = B11 + B22; S7 = A12 - A22; S8 = B21 + B22;
			S9 = A11 - A21; S10 = B11 + B12;
			square_matrix_multiply_recursive(A11, S1, P1);
			square_matrix_multiply_recursive(S2, B22, P2);
			square_matrix_multiply_recursive(S3, B11, P3);
			square_matrix_multiply_recursive(A22, S4, P4);
			square_matrix_multiply_recursive(S5, S6, P5);
			square_matrix_multiply_recursive(S7, S8, P6);
			square_matrix_multiply_recursive(S9, S10, P7);
			C11 = P5 + P4 - P2 + P6;
			C12 = P1 + P2;
			C21 = P3 + P4;
			C22 = P5 + P1 - P3 - P7;
			C = FourMerge(C11, C12, C21, C22);
		}
	}
}
