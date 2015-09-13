#include <iostream>
#include <complex>
#include <cmath>
#include "matrices.h"

/*
	This is a "how to" code-like to show how to use
	the Matrix class properly.
	@date March 10th, 2015
*/

using namespace std;

int main()
{
	// Identity Matrix of complex values
	auto matrix1 = Matrix<complex<double>>::identity(3, complex<double>(1, 2));
	auto matrix2 = Matrix<double>(3,3,1); // 3 by 3 matrix of ones
	
	auto matrix3 = multiplyMatrices(matrix1, matrix2); 
	auto matrix4 = matrix1 + matrix2; // Supported operators = {+, -, *, /}
	auto matrix5 = applyFunctorToMatrices(matrix2, matrix2, [](double x, double y) {
		return sqrt(x*x + (y + 1)*y); // 'x' is from matrix 2 and in this case 'y' is also from matrix 2
	});
	
	cout << matrix1 << endl;
	cout << matrix2 << endl;
	cout << matrix3 << endl;
	cout << matrix4 << endl;
	cout << matrix5 << endl;
	
	matrix4 -= complex<double>(3, -1); // Supported operators = {+=, -=, *=, /=}
	cout << matrix4 << endl;
	
	matrix4.applyFunctor([](const complex<double>& c) {
		return pow(c, 3); // Each element of the matrix4 is going to be raised to the 3 power
	});
	cout << matrix4 << endl;
	

	return 0;
}