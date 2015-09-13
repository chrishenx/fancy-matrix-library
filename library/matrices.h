/*
  @file matrices.h It defines the Matrix class
	©2015 Christian González
	
	The MIT License (MIT)

  Copyright (c) 2015 Christian González León

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 */

#ifndef MATRICES_H
#define MATRICES_H

#include <vector>
#include <ostream>

/**
 * Matrix class
 * Model of matrix for matlab-like usage
 */
template <typename T>
class Matrix {
 public:
	Matrix();
	Matrix(int rows, int columns, const T& value = T());
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	Matrix(std::initializer_list<std::initializer_list<T>> il);
	Matrix(std::initializer_list<T> il);
  template <typename K>
	Matrix(const Matrix<K>& other);
	template <typename K>
	Matrix(Matrix<K>&& other);
	~Matrix() { clear(); }
	
	bool insertRow(int row, const T& value = T());	
	bool insertColumn(int column, const T& value = T());
	bool deleteRow(int row);
	bool deleteColumn(int column);
  
	Matrix transpose() const;
	
	template <typename K>
	bool appendHorizontally(const Matrix<K>& other, int column);
	template <typename K>
	bool appendVertically(const Matrix<K>& other, int row);
	template <typename Functor>
	void applyFunctor(const Functor& functor);
  template <typename K, typename Functor>
	void applyFunctor(const Matrix<K>& other, const Functor& functor);
	
	void clear();
	
	int getRows() const { return rows; }
	int getColumns() const { return columns; }
	int numberOfCells() const { return rows * columns; }	
	bool isEmpty() const { return rows == 0; }
	template <typename K>
	bool hasSameDimensionsAs(const Matrix<K>& other) const {
		return rows == other.getRows() and columns == other.getColumns();
	}
	
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	template <typename K>
	Matrix& operator=(const Matrix<K>& other);
	template <typename K>
	Matrix& operator=(Matrix<K>&& other);
  
  Matrix operator-() const;
  Matrix operator+() const;
	/*
		The following four member operators apply the corresponding
		operation using a scalar type.
		The method "applyFunctor" have the same meaning but
		using a unary functor instead and operator.
	*/
	template <typename K>
	Matrix& operator*=(const K& multiplier);
	template <typename K>
	Matrix& operator/=(const K& divisor);
	template <typename K>
	Matrix& operator+=(const K& adding);
	template <typename K>
	Matrix& operator-=(const K& subtrahend);
  
	template <typename K>
	Matrix& operator*=(const Matrix<K>& other);
	template <typename K>
	Matrix& operator/=(const Matrix<K>& other);
	template <typename K>
	Matrix& operator+=(const Matrix<K>& other);
	template <typename K>
	Matrix& operator-=(const Matrix<K>& other);
  
	T& operator()(int row, int column) { return matrix[row][column]; }
	const T& operator()(int row, int column) const { return matrix[row][column]; }
	const std::vector<T>& operator[](int index) const { return matrix[index]; }
	
	static Matrix identity(int rank, const T& value);
 private:
	std::vector<std::vector<T>> matrix;
	int rows, columns;
  
  std::vector<T>& operator[](int index) { return matrix[index]; }
  
  template <typename E, typename U, typename Functor> friend auto applyFunctorToMatrices(const Matrix<E>&, const Matrix<U>&, 
    const Functor& functor) -> Matrix<decltype(functor(E(), U()))>;
};

// The overloaded arithmetic operators are in the matrices.cpp file
	
template <typename T, typename K, typename Functor>
auto applyFunctorToMatrices(const Matrix<T>&, const Matrix<K>&, 
    const Functor& functor) -> Matrix<decltype(functor(T(), K()))>;

template <typename T, typename K, typename Functor>
auto applyFunctorToMatrixAndScalar(const Matrix<T>&, const K&,
    const Functor& functor) -> Matrix<decltype(functor(T(), K()))>;
	
template <typename T, typename K>
auto multiplyMatrices(const Matrix<T>&, const Matrix<K>&) 
	-> Matrix<decltype(T() * K())>;	


#include "matrices.cpp"
#include "matrix_operators.h"

using dMatrix = Matrix<double>;
using fMatrix = Matrix<float>;
using iMatrix = Matrix<int>;

#endif // MATRICES_H