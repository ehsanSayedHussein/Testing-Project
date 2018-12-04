#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>

using namespace std;
typedef vector<vector<int>> matrix;
class Matrix {
private:
public:
	matrix zero(int n,int m);
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

matrix Matrix::zero(int n,int m) {
	return matrix(n, vector<int>(m, 0));
}

matrix Matrix::identity(int n) {
	matrix ret = zero(n,n);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			ret[i][j] = (i == j);
	return ret;
}
matrix Matrix::rowSwitching(matrix A, int firstRow, int secondRow) {
	matrix ret = zero(A.size(), A.size());
	int temp = 0;
	ret = A;
	for (int i = 0; i < A.size(); i++) {
		ret[firstRow-1][i] = A[secondRow-1][i];
		ret[secondRow-1][i] = A[firstRow-1][i];
	}
	return ret;
}
matrix Matrix::multiply(matrix a, matrix b) {
	matrix ret=zero(a[0].size(),b.size());
	for (int i = 0; i<a.size(); i++)
		for (int j = 0; j<a[i].size(); j++) {
			ret[i][j] = 0;
			for (int k = 0; k<a[i].size(); k++)
				ret[i][j] = ret[i][j] + a[i][k] * b[k][j];
		}
	return ret;
}
matrix Matrix::add(matrix a, matrix b) {
	matrix ret = zero(a.size(),b[0].size());
	for (int i = 0; i<a.size(); i++)
		for (int j = 0; j<b[i].size(); j++)
			ret[i][j] = a[i][j] + b[i][j];
	return ret;
}
matrix Matrix::transpose(matrix A) {
	matrix res = A;
	int n = A.size();
	int m = A[0].size(); 
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			res[j][i] = A[i][j];
	return res;
}
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

int Matrix::determinant(matrix mat, int n)
{
	int D = 0;
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


SUITE(MatrixOperationsTest)
{
	class myMatrix
	{
	public:
		 Matrix m;
	};
	TEST_FIXTURE(myMatrix, checkDeterminant)
	{
		//This is my matrix 
		// 7 8 5
		// 8 9 2 
		// 4 5 8
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		CHECK_EQUAL(-18, m.determinant(mymat, 3));
	}
	TEST_FIXTURE(myMatrix, checkPower)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		matrix expected;
		expected.push_back(vector<int>({ 433,430,699 }));
		expected.push_back(vector<int>({ 612,603,981 }));
		expected.push_back(vector<int>({ 912,894,1458 }));
		CHECK_ARRAY2D_CLOSE(expected, m.power(mymat, 3),3,3,0);
	}

	TEST_FIXTURE(myMatrix, checkTranspose)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		matrix expected;
		expected.push_back(vector<int>({ 1,3,6 }));
		expected.push_back(vector<int>({ 3,4,4 }));
		expected.push_back(vector<int>({ 4,5,8 }));
		CHECK_ARRAY2D_CLOSE(expected, m.transpose(mymat), 3, 3, 0);
	}
	TEST_FIXTURE(myMatrix, checkAdd)
	{
		matrix mymat1;
		mymat1.push_back(vector<int>({ 1,3,4 }));
		mymat1.push_back(vector<int>({ 3,4,5 }));
		mymat1.push_back(vector<int>({ 6,4,8 }));
		matrix mymat2;
		mymat2.push_back(vector<int>({ 8,6,8 }));
		mymat2.push_back(vector<int>({ 6,5,4 }));
		mymat2.push_back(vector<int>({ 2,0,7 }));

		matrix expected;
		expected.push_back(vector<int>({ 9,9,12 }));
		expected.push_back(vector<int>({ 9,9,9  }));
		expected.push_back(vector<int>({ 8,4,15 }));
		CHECK_ARRAY2D_CLOSE(expected, m.add(mymat1,mymat2), 3, 3, 0);
	}

	TEST_FIXTURE(myMatrix, rowSwitch)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));

		matrix expected;
		expected.push_back(vector<int>({ 6,4,8 }));
		expected.push_back(vector<int>({ 3,4,5 }));
		expected.push_back(vector<int>({ 1,3,4 }));
		CHECK_ARRAY2D_CLOSE(expected, m.rowSwitching(mymat,1,3), 3, 3, 0);
	}

	TEST_FIXTURE(myMatrix, checkTime)
	{
		{
			UNITTEST_TIME_CONSTRAINT(1000);
			matrix mymat = m.zero(50, 50);
			for (int i = 0; i < 50; i++)
				for (int j = 0; j < 50; j++)
					mymat[i][j] = rand() % 50;
			matrix res = m.power(mymat, 2);
		}
	}

	TEST_FIXTURE(myMatrix, myTest)
	{
		matrix container;
		container.push_back(vector<int>({ 1,3,4 }));
		container.push_back(vector<int>({ 3,4,5 }));
		container.push_back(vector<int>({ 6,4,8 }));
		REQUIRE CHECK(!container.empty());
		cout << "Continue" << endl;
		CHECK_EQUAL(1, container[0][0]); 
	}

	TEST_FIXTURE(myMatrix, checkSymmetric)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		CHECK_THROW(m.power(mymat, 3), std::runtime_error);
	}

}

int main(int, const char *[])
{
	return UnitTest::RunAllTests();
}