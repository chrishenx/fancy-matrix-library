/*
  @file matrices.h It defines the Matrix class
	© 2015 Christian González
	
	This file is part of the "Fancy Matrix" library.

    "Fancy Matrix" library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    "Fancy Matrix" library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with "Fancy Matrix" library.  If not, see <http://www.gnu.org/licenses/>.
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