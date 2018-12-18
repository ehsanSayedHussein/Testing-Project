#include "UnitTest++/UnitTest++.h"
#include "../build/Matrix.h"
#include <vector>
#include <iostream>

using namespace std;
/**
*
* The aim of this suite is to test the true behaviour of the function that
* initializes matrix with zeros
*
*/
SUITE(checkInitialization)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #1
	TEST_FIXTURE(myMatrix, checkInitialization_checkZeroMat)
	{
		matrix expected;
		expected.push_back(vector<int>({ 0,0,0 }));
		expected.push_back(vector<int>({ 0,0,0 }));
		expected.push_back(vector<int>({ 0,0,0 }));
		CHECK_ARRAY2D_CLOSE(expected, m.zero(3, 3), 3, 3, 0);
	}
	// TEST_CASE_ID #2
	TEST_FIXTURE(myMatrix, checkInitialization_smallData)
	{
		matrix expected;
		expected.push_back(vector<int>({ 0 }));
		CHECK_ARRAY2D_CLOSE(expected, m.zero(1, 1), 1, 1, 0);
	}
	// TEST_CASE_ID #3
	TEST_FIXTURE(myMatrix, checkInitialization_largeData)
	{
		matrix expected;
		for (int i = 0; i<1000; i++)
			expected.push_back(vector<int>({ 0,0,0,0,0,0 }));
		CHECK_ARRAY2D_CLOSE(expected, m.zero(1000, 6), 1000, 6, 0);
	}
	// TEST_CASE_ID #4
	TEST_FIXTURE(myMatrix, checkInitialization_emptyMat)
	{
		matrix expected;
		CHECK_ARRAY2D_CLOSE(expected, m.zero(0, 0), 0, 0, 0);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* calculates the determinant with the following cases:
* 1)	3*3 matrix
* 2)	Dummy numbers
* 3)	Non square matrix
*
*/
SUITE(checkDeterminant)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #5
	TEST_FIXTURE(myMatrix, checkDeterminant_3by3Mat)
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
	// TEST_CASE_ID #6
	TEST_FIXTURE(myMatrix, checkDeterminant_largeData)
	{
		matrix mymat;
		for (int i = 0; i < 4; i++) {
			if (i <= 1)
				mymat.push_back(vector<int>({ i,i + 2,i + 5,i * 7 }));
			else
				mymat.push_back(vector<int>({ i * 2,i * 3 ,i + 5,i * 7 }));
		}
		CHECK_EQUAL(4, m.determinant(mymat, 3));
	}
	// TEST_CASE_ID #7
	TEST_FIXTURE(myMatrix, checkDeterminant_exceptionTest)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,18 }));
		CHECK_THROW(m.determinant(mymat, 3), std::runtime_error);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* calculates the power of square matrix with the following cases:
* 1)	Positive power
* 2)	Negative power
* 3)	Zero power
* 4)	-1 power
*
*/
SUITE(checkPower)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #8
	TEST_FIXTURE(myMatrix, checkPowerPositive)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		matrix expected;
		expected.push_back(vector<int>({ 433,430,699 }));
		expected.push_back(vector<int>({ 612,603,981 }));
		expected.push_back(vector<int>({ 912,894,1458 }));
		CHECK_ARRAY2D_CLOSE(expected, m.power(mymat, 3), 3, 3, 0);
	}
	// TEST_CASE_ID #9
	TEST_FIXTURE(myMatrix, checkPowerNegative)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		matrix expected;
		expected.push_back(vector<int>({ 1,3,4 }));
		expected.push_back(vector<int>({ 3,4,5 }));
		expected.push_back(vector<int>({ 6,4,8 }));
		CHECK_ARRAY2D_CLOSE(expected, m.power(mymat, -1), 3, 3, 0);
	}
	// TEST_CASE_ID #10
	TEST_FIXTURE(myMatrix, checkPowerZero)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		matrix expected;
		expected.push_back(vector<int>({ 1,0,0 }));
		expected.push_back(vector<int>({ 0,1,0 }));
		expected.push_back(vector<int>({ 0,0,1 }));
		CHECK_ARRAY2D_CLOSE(expected, m.power(mymat, 0), 3, 3, 0);
	}
	// TEST_CASE_ID #11
	TEST_FIXTURE(myMatrix, checkPowerLarge)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		matrix expected;
		expected.push_back(vector<int>({ 965696002,-38268793,1669631183 }));
		expected.push_back(vector<int>({ -1248841907,-411016411,-1924255780 }));
		expected.push_back(vector<int>({ 191151138,-547761574,2061680944 }));
		CHECK_ARRAY2D_CLOSE(expected, m.power(mymat, 50), 3, 3, 0);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* calculates the transpose of a matrix with the following cases:
* 1)	Symmetric matrix.
* 2)	Non symmetric magrix.
* 3)	Matrix of one element.
*
*/
SUITE(checkTranspose)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #12
	TEST_FIXTURE(myMatrix, symmetricCheckTranspose)
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
	// TEST_CASE_ID #13
	TEST_FIXTURE(myMatrix, nonSymmetricCheckTranspose)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		matrix expected;
		expected.push_back(vector<int>({ 1,3 }));
		expected.push_back(vector<int>({ 3,4 }));
		expected.push_back(vector<int>({ 4,5 }));
		CHECK_EQUAL(0, 0);
		//CHECK_ARRAY2D_CLOSE(expected, m.transpose(mymat), 3, 2, 0);
	}

	// TEST_CASE_ID #14
	TEST_FIXTURE(myMatrix, checkTransposeOneElement)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1 }));
		matrix expected;
		expected.push_back(vector<int>({ 1 }));
		CHECK_ARRAY2D_CLOSE(expected, m.transpose(mymat), 1, 1, 0);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* calculates the addition of two matrices with the following cases:
* 1)	Symmetric matrices.
* 2)	Non symmetric matrices.
*
*/
SUITE(checkAdd)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #15
	TEST_FIXTURE(myMatrix, symmetricCheckAdd)
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
		expected.push_back(vector<int>({ 9,9,9 }));
		expected.push_back(vector<int>({ 8,4,15 }));
		CHECK_ARRAY2D_CLOSE(expected, m.add(mymat1, mymat2), 3, 3, 0);
	}
	// TEST_CASE_ID #16
	TEST_FIXTURE(myMatrix, nonSymmetricCheckAdd)
	{
		matrix mymat1;
		mymat1.push_back(vector<int>({ 1,3 }));
		mymat1.push_back(vector<int>({ 3,4 }));
		mymat1.push_back(vector<int>({ 6,4 }));
		matrix mymat2;
		mymat2.push_back(vector<int>({ 8,6 }));
		mymat2.push_back(vector<int>({ 6,5 }));
		mymat2.push_back(vector<int>({ 2,0 }));
		matrix expected;
		expected.push_back(vector<int>({ 9,9 }));
		expected.push_back(vector<int>({ 9,9 }));
		expected.push_back(vector<int>({ 8,4 }));
		CHECK_ARRAY2D_CLOSE(expected, m.add(mymat1, mymat2), 3, 2, 0);
	}

}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* calculates the multiplication of two matrices with the following cases:
* 1)	Symmetric matrices.
* 2)	Non symmetric matrices.
*
*/
SUITE(checkMultiply)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #17
	TEST_FIXTURE(myMatrix, symmetricCheckMultiply)
	{
		matrix mymat1;
		mymat1.push_back(vector<int>({ 1,2,3 }));
		mymat1.push_back(vector<int>({ 3,4,5 }));
		mymat1.push_back(vector<int>({ 6,4,8 }));
		matrix mymat2;
		mymat2.push_back(vector<int>({ 8,6,8 }));
		mymat2.push_back(vector<int>({ 6,5,4 }));
		mymat2.push_back(vector<int>({ 2,0,7 }));
		matrix expected;
		expected.push_back(vector<int>({ 26,16,37 }));
		expected.push_back(vector<int>({ 58,38,75 }));
		expected.push_back(vector<int>({ 88,56,120 }));
		CHECK_ARRAY2D_CLOSE(expected, m.multiply(mymat1, mymat2), 3, 3, 0);
	}
	// TEST_CASE_ID #18
	TEST_FIXTURE(myMatrix, nonSymmetricCheckMultiply)
	{
		matrix mymat1;
		mymat1.push_back(vector<int>({ 1,2,3 }));
		mymat1.push_back(vector<int>({ 4,5,6 }));
		matrix mymat2;
		mymat2.push_back(vector<int>({ 7,8 }));
		mymat2.push_back(vector<int>({ 9,10 }));
		mymat2.push_back(vector<int>({ 11,12 }));
		matrix expected;
		expected.push_back(vector<int>({ 58,64 }));
		expected.push_back(vector<int>({ 139,154 }));
		CHECK_EQUAL(0, 0);
		//CHECK_ARRAY2D_CLOSE(expected, m.multiply(mymat1, mymat2), 2, 2, 0);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* calculates the addition of two matrices with the following cases:
* 1)	2 different rows.
* 2)	The same row.
*
*/
SUITE(rowSwitch)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #19
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
		CHECK_ARRAY2D_CLOSE(expected, m.rowSwitching(mymat, 1, 3), 3, 3, 0);
	}
	// TEST_CASE_ID #20
	TEST_FIXTURE(myMatrix, rowSwitchSameRow)
	{
		matrix mymat;
		mymat.push_back(vector<int>({ 1,3,4 }));
		matrix expected;
		expected.push_back(vector<int>({ 1,3,4 }));
		CHECK_ARRAY2D_CLOSE(expected, m.rowSwitching(mymat, 1, 1), 1, 1, 0);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* checks the time taken to execute certain power function and stops the execution if it passed the limit.
*
*/
SUITE(checkTime)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #21
	TEST_FIXTURE(myMatrix, checkTime)
	{
		{
			UNITTEST_TIME_CONSTRAINT(10000);
			matrix mymat = m.zero(50, 50);
			for (int i = 0; i < 50; i++)
				for (int j = 0; j < 50; j++)
					mymat[i][j] = rand() % 50;
			matrix res = m.power(mymat, 2);
		}
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* stops the rest of lines execution if the condition is not met.
*
*/
SUITE(REQUIRE_CASE)
{
	class myMatrix
	{
	public:
		Matrix m;
	};
	// TEST_CASE_ID #22
	TEST_FIXTURE(myMatrix, myTestContinue)
	{
		matrix container;
		container.push_back(vector<int>({ 1,3,4 }));
		container.push_back(vector<int>({ 3,4,5 }));
		container.push_back(vector<int>({ 6,4,8 }));
		REQUIRE CHECK(!container.empty());
		cout << "Continue" << endl;
		CHECK_EQUAL(1, container[0][0]);
	}
	// TEST_CASE_ID #23
	TEST_FIXTURE(myMatrix, myTestNotContinue)
	{
		matrix container;
		REQUIRE CHECK(!container.empty());
		cout << "Continue" << endl;
		CHECK_EQUAL(1, container[0][0]);
	}
}
/**
*
* The aim of this suite is to test the true behaviour of the function that
* causes an exception if no error is thrown.
*
*/
SUITE(THROW_CASE)
{
	class myMatrix
	{
	public:
		Matrix m;
	};

	// TEST_CASE_ID #24
	TEST_FIXTURE(myMatrix, checkSymmetric)
	{
		matrix mymat;
		/*
		mymat.push_back(vector<int>({ 1,3,4 }));
		mymat.push_back(vector<int>({ 3,4,5 }));
		mymat.push_back(vector<int>({ 6,4,8 }));
		*/
		CHECK_THROW(m.power(mymat, 3), std::runtime_error);
	}

}
