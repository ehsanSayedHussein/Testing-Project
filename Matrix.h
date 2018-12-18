#pragma once
#include <vector>
#include <iostream>
using namespace std;
typedef vector<vector<int>> matrix;
class Matrix {
private:
public:
	matrix zero(int n, int m);
	matrix identity(int n);
	matrix multiply(matrix a, matrix b);
	matrix add(matrix a, matrix b);
	matrix transpose(matrix A);
	matrix power(matrix A, int p);
	matrix rowSwitching(matrix A, int firstRow, int secondRow);
	void getCofactor(matrix& mat, matrix& temp, int p, int q, int n);
	int determinant(matrix mat, int n);
};

typedef vector<vector<int>> matrix;
/**
* Initializes the matrix with zeros
*
* @param	n number of rows
* @param	m number of cols
*
* @return	the initialized matrix
*
*/
matrix Matrix::zero(int n, int m) {
	return matrix(n, vector<int>(m, 0));
}
/**
* Calculates the identity matrix
*
* @param	n number of rows
*
* @return	the identity matrix of size n
*
*/
matrix Matrix::identity(int n) {
	matrix ret = zero(n, n);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			ret[i][j] = (i == j);
	return ret;
}
/**
* Switches two rows
*
* @param	A matrix
* @param	firstRow number of the first row
* @param	secondRow number of the second row
*
* @return	the initialized matrix
*
*/
matrix Matrix::rowSwitching(matrix A, int firstRow, int secondRow) {
	matrix ret = zero(A.size(), A.size());
	int temp = 0;
	ret = A;
	for (int i = 0; i < A.size(); i++) {
		ret[firstRow - 1][i] = A[secondRow - 1][i];
		ret[secondRow - 1][i] = A[firstRow - 1][i];
	}
	return ret;
}
/**
* Multiplies two matrices
*
* @param	a matrix
* @param	b matrix
*
* @return	the result
*
*/
matrix Matrix::multiply(matrix a, matrix b) {
	matrix ret = zero(a[0].size(), b.size());
	for (int i = 0; i<a.size(); i++)
		for (int j = 0; j<a[i].size(); j++) {
			ret[i][j] = 0;
			for (int k = 0; k<a[i].size(); k++)
				ret[i][j] = ret[i][j] + a[i][k] * b[k][j];
		}
	return ret;
}
/**
* Adds two matrices
*
* @param	a matrix
* @param	b matrix
*
* @return	the result
*
*/
matrix Matrix::add(matrix a, matrix b) {
	matrix ret = zero(a.size(), b[0].size());
	for (int i = 0; i<a.size(); i++)
		for (int j = 0; j<b[i].size(); j++)
			ret[i][j] = a[i][j] + b[i][j];
	return ret;
}
/**
* Transposes a matrix
*
* @param	A matrix\
*
* @return	the transpose of matrix A
*
*/
matrix Matrix::transpose(matrix A) {
	matrix res = A;
	int n = A.size();
	int m = A[0].size();
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			res[j][i] = A[i][j];
	return res;
}
/**
* Calculates the power of a matrix
*
* @param	A matrix
*
* @param	p power value
* @return	the result
*
*/
matrix Matrix::power(matrix A, int p) {
	if (!A.size()) {
		throw std::runtime_error("empty matrix!");
	}
	for (int i = 0; i < A.size(); i++) {
		if (A[i].size() != A.size()) {
			throw std::runtime_error("not square matrix!");
		}
	}
	if (!p)return identity(A.size());
	matrix res = power(A, p / 2);
	res = multiply(res, res);
	if (p & 1)res = multiply(res, A);
	return res;
}

void Matrix::getCofactor(matrix& mat, matrix& temp, int p, int q, int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = mat[row][col];
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}
/**
* Calculates the determinant of a square mat
*
* @param	a matrix
* @param	n matrix size
*
* @return	the determinant
*
*/
int Matrix::determinant(matrix mat, int n)
{
	int D = 0;
	for (int i = 0; i < mat.size(); i++) {
		if (mat[i].size() != mat.size()) {
			throw std::runtime_error("not square matrix!");
		}
	}
	if (n == 1)
		return mat[0][0];
	matrix temp(n, vector<int>(n, 0));
	int sign = 1;
	for (int f = 0; f < n; f++)
	{
		getCofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f] * determinant(temp, n - 1);
		sign = -sign;
	}
	return D;
}
