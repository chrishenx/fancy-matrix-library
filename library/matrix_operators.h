/*
  @file matrix_operators.h Implementation of the non-member operations related to the matrix class
  ©2015 Christian González León
  
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

#ifndef MATRIX_OPERATORS_H
#define MATRIX_OPERATORS_H

template <typename T>
std::ostream& operator<<(std::ostream& outputStream, const Matrix<T>& matrix) {
  const int rows = matrix.getRows();
  const int columns = matrix.getColumns();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      outputStream << matrix[i][j];
      if (j < columns - 1) outputStream << ',';
      outputStream << ' ';
    }
    outputStream << '\n';
  }
  return outputStream;
}

/* 
	The following operators apply the corresponding binary 
	operation of the corresponding elements of the two matrices given 
	or one matrix and a scalar value and returns a new matrix.
    If the matrices have not the same dimensions, 
	the matrix returned will be empty.
	The function "applyFunctorToMatrices" have the same meaning but
	using a binary functor instead and operator.
*/

template <typename T, typename K>
inline auto operator*(const Matrix<T>& matrix1, const Matrix<K>& matrix2) 
    -> Matrix<decltype(T() * K())> {
  if (matrix1.hasSameDimensionsAs(matrix2)) {
    return applyFunctorToMatrices(matrix1, matrix2, 
      [](const T& x, const K& y) {
        return x * y;
    });
  }
  return {};
}

template <typename T, typename K>
inline auto operator/(const Matrix<T>& matrix1, const Matrix<K>& matrix2) 
    -> Matrix<decltype(T() / K())> {
  if (matrix1.hasSameDimensionsAs(matrix2)) {
    return applyFunctorToMatrices(matrix1, matrix2, 
      [](const T& x, const K& y) {
        return x / y;
    });
  }
  return {};
}

template <typename T, typename K>
inline auto operator+(const Matrix<T>& matrix1, const Matrix<K>& matrix2) 
    -> Matrix<decltype(T() + K())> {
  if (matrix1.hasSameDimensionsAs(matrix2)) {
    return applyFunctorToMatrices(matrix1, matrix2, 
      [](const T& x, const K& y) {
        return x + y;
    });
  }
  return {};
}

template <typename T, typename K>
inline auto operator-(const Matrix<T>& matrix1, const Matrix<K>& matrix2) 
    -> Matrix<decltype(T() - K())> {
  if (matrix1.hasSameDimensionsAs(matrix2)) {
    return applyFunctorToMatrices(matrix1, matrix2, 
      [](const T& x, const K& y) {
        return x - y;
    });
  }
  return {};
}

template <typename T, typename K>
inline auto operator*(const Matrix<T>& matrix, const K& value) 
	  -> Matrix<decltype(T() * K())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return x * y;
  });
}

template <typename T, typename K>
inline auto operator*(const K& value, const Matrix<T>& matrix) 
    -> Matrix<decltype(T() * K())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return x * y;
  });
}
	
template <typename T, typename K>
inline auto operator/(const Matrix<T>& matrix, const K& value) 
	  -> Matrix<decltype(T() / K())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return x / y;
  });
}

template <typename T, typename K>
inline auto operator/(const K& value, const Matrix<T>& matrix) 
    -> Matrix<decltype(K() / T())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return y / x;
  });
}
	
template <typename T, typename K>
inline auto operator+(const Matrix<T>& matrix, const K& value) 
    -> Matrix<decltype(T() + K())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return x + y;
  });
}

template <typename T, typename K>
inline auto operator+(const K& value, const Matrix<T>& matrix)      
    -> Matrix<decltype(T() + K())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return x + y;
  });
}
	
template <typename T, typename K>
inline auto operator-(const Matrix<T>& matrix, const K& value) 
    -> Matrix<decltype(T() - K())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return x - y;
  });
}

template <typename T, typename K>
inline auto operator-(const K& value, const Matrix<T>& matrix) 
    -> Matrix<decltype(K() - T())> {
  return applyFunctorToMatrixAndScalar(matrix, value, 
    [](const T& x, const K& y) {
      return y - x;
  });
}

#endif // MATRIX_OPERATORS_H