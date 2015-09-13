/*
    @file matrix_operators.h Implementation of the non-member operations related to the matrix class
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