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

#ifndef MATRICES_CPP
#define MATRICES_CPP

#include <iostream>
 
/**
 * Matrix class implementation
 */
 
// CONSTRUCTORS

template <typename T>
Matrix<T>::Matrix()
{
  rows = 0;
  columns = 0;
}

/**
 * It creates a Matrix with a specific number of rows and columns 
 * and also with an optional default value for each cell.
 */
template <typename T>
Matrix<T>::Matrix(int rows, int columns, const T& value)
    : matrix (rows, std::vector<T>(columns, value)) {
  this->rows = rows;
  this->columns = columns;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : matrix (other.matrix) {
  rows = other.rows;
  columns = other.columns;
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other)
    : matrix (std::move(other.matrix)) {
  rows = other.rows;
  columns = other.columns;
  other.rows = 0;
  other.columns = 0;
  // std::cout << "Move contructor" << std::endl;
}

template <typename T>
template <typename K>
Matrix<T>::Matrix(const Matrix<K>& other)
    : matrix (other.getRows(), std::vector<T>(other.getColumns())) {
  rows = other.getRows();
  columns = other.getColumns();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix[i][j] = other[i][j];
    }
  }
}

template <typename T>
template <typename K>
Matrix<T>::Matrix(Matrix<K>&& other)
    : matrix (other.getRows(), std::vector<T>(other.getColumns())) {
  rows = other.getRows();
  columns = other.getColumns();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix[i][j] = other[i][j];
    }
  }
  other.clear();
}

/**
 * Because of a Matrix must be squared and a initializer_list may not,
 * this constructor creates a matrix sized according to:
 *    rows = number of initializer_lists
 *    columns = number of elements in the first initializer_list
 */
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> il) {
  if (il.size() > 0 and (*begin(il)).size() > 0) {
    rows = il.size();
    columns = (*begin(il)).size();
    matrix = std::vector<std::vector<T>>(rows, std::vector<T>(columns));
    auto rowsIt = begin(il);
    for (int i = 0; i < rows; i++, rowsIt++) {
      auto columnsIt = begin(*rowsIt);
      for (int j = 0; j < columns; j++) {
        if (columnsIt != end(*rowsIt)) {
          matrix[i][j] = *columnsIt;
          columnsIt++;
        }
      }
    }
  }
}

/**
 * It creates a Matrix with one row and initializer_list.size() columns.
 */
template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> il)
    : matrix (1, il) {
  rows = 1;
  columns = il.size();
}

// Operators

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
  matrix = other.matrix;
  rows = other.rows;
  columns = other.columns;
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) {
  matrix = std::move(other.matrix);
  rows = other.rows;
  columns = other.columns;
  other.rows = 0;
  other.columns = 0;
  // std::cout << "Move assingation" << std::endl;
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator=(const Matrix<K>& other) {
  matrix.clear();
  rows = other.getRows();
  columns = other.getColumns();
  matrix = std::vector<std::vector<T>>(rows, std::vector<T>(columns));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix[i][j] = other[i][j];
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator=(Matrix<K>&& other) {
  matrix.clear();
  rows = other.getRows();
  columns = other.getColumns();
  matrix = std::vector<std::vector<T>>(rows, std::vector<T>(columns));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix[i][j] = other[i][j];
    }
  }
  other.clear();
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
  Matrix resultingMatrix(*this);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      resultingMatrix.matrix[i][j] = -matrix[i][j];
    }
  }
  return resultingMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator+() const {
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator*=(const K& multiplier) {
  for (std::vector<T>& vector : matrix) {
    for (T& value : vector) {
      value *= multiplier;
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator/=(const K& divisor) {
  for (std::vector<T>& vector : matrix) {
    for (T& value : vector) {
      value /= divisor;
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator+=(const K& adding) {
  for (std::vector<T>& vector : matrix) {
    for (T& value : vector) {
      value += adding;
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator-=(const K& subtrahend) {
  for (std::vector<T>& vector : matrix) {
    for (T& value : vector) {
      value -= subtrahend;
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator*=(const Matrix<K>& other) {
  if (hasSameDimensionsAs(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix[i][j] *= other[i][j];
      }
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator/=(const Matrix<K>& other) {
  if (hasSameDimensionsAs(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix[i][j] /= other[i][j];
      }
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator+=(const Matrix<K>& other) {
  if (hasSameDimensionsAs(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix[i][j] += other[i][j];
      }
    }
  }
  return *this;
}

template <typename T>
template <typename K>
Matrix<T>& Matrix<T>::operator-=(const Matrix<K>& other) {
  if (hasSameDimensionsAs(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix[i][j] -= other[i][j];
      }
    }
  }
  return *this;
}

// Utilities

template <typename T>
bool Matrix<T>::insertRow(int row, const T& value) {
  if (row < 0 or row > rows) return false;
  matrix.insert(begin(matrix) + row, std::vector<T>(columns, value)); 
  rows++;
  return true;
}

template <typename T>
bool Matrix<T>::insertColumn(int column, const T& value) {
  if (column < 0 or column > columns) return false;
  for (std::vector<T>& vector: matrix) {
    vector.insert(begin(vector) + column, value);
  }
  columns++;
  return true;
}

template <typename T>
bool Matrix<T>::deleteRow(int row) {
  if (row < 0 or row >= rows) return false;
  matrix.erase(begin(matrix) + row);
  rows--;
  return true;
}

template <typename T>
bool Matrix<T>::deleteColumn(int column) {
  if (column < 0 or column >= columns) return false;
  for (std::vector<T>& vector: matrix) {
    vector.erase(begin(vector) + column);
  }
  columns--;
  return true;
}

template <typename T>
template <typename K>
bool Matrix<T>::appendHorizontally(const Matrix<K>& other, int column) {
  if (column < 0 or column > columns or rows != other.getRows()) return false;
  for (int i = 0; i < rows; i++) {
    matrix[i].insert(
      begin(matrix[i]) + column, begin(other[i]), 
      begin(other[i]) + other.getColumns()
    );
  }
  columns += other.getColumns();
  return true;
}

template <typename T>
template <typename K>
bool Matrix<T>::appendVertically(const Matrix<K>& other, int row) {
  if (row < 0 or row > rows or columns != other.getColumns()) return false;
  for (int i = 0; i < other.getRows(); i++) {
    matrix.push_back(
      std::vector<T>(begin(other[i]), begin(other[i]) + other.getRows())
    );
  }
  rows += other.getRows();
  return true;
}

/**
 * It applies an unary function to each element in the Matrix.
 * I recommend to use a lamda object instead of writing a whole functor class.
 */
template <typename T>
template <typename Functor>
void Matrix<T>::applyFunctor(const Functor& functor) {
  for (std::vector<T>& vector : matrix) {
    for (T& value : vector) {
      value = std::move(functor(value));
    }
  }
}

template <typename T>
template <typename K, typename Functor>
void Matrix<T>::applyFunctor(const Matrix<K>& other, const Functor& functor) {
  if (hasSameDimensionsAs(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix[i][j] = std::move(functor(matrix[i][j], other[i][j]));
      }
    }
  }
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
  Matrix resultingMatrix(columns, rows);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      resultingMatrix.matrix[j][i] = matrix[i][j];
    }
  }
  return resultingMatrix;
}

template <typename T>
void Matrix<T>::clear() {
  rows = 0;
  columns = 0;
  matrix.clear();
}

/**
 * It creates a squared Matrix with the given rank and 
 * with given the value in the main diagonal.
 */
template <typename T>
Matrix<T> Matrix<T>::identity(int rank, const T& value) {
  Matrix resultingMatrix(rank, rank);
  for (int i = 0; i < rank; i++) {
    resultingMatrix.matrix[i][i] = value;
  }
  return resultingMatrix;
}

// Functions

template <typename T, typename K, typename Functor>
auto applyFunctorToMatrices(const Matrix<T>& matrix1, const Matrix<K>& matrix2,
    const Functor& functor) -> Matrix<decltype(functor(T(), K()))> {
  if (matrix1.hasSameDimensionsAs(matrix2)) {
    const int rows = matrix1.getRows();
    const int columns = matrix1.getColumns();
    Matrix<decltype(functor(T(), K()))> resultingMatrix(rows, columns);
    for (int i = 0; i < rows; i++) {
      const auto& row1 = matrix1[i];
      const auto& row2 = matrix2[i];
      auto& resultingRow = resultingMatrix[i];
      for (int j = 0; j < columns; j++) {
        resultingRow[j] = std::move(functor(row1[j], row2[j]));
      }
    }
    return resultingMatrix;
  }
  return {};
}

template <typename T, typename K, typename Functor>
auto applyFunctorToMatrixAndScalar(const Matrix<T>& matrix, const K& scalar,
    const Functor& functor) -> Matrix<decltype(functor(T(), K()))> {
  const int rows = matrix.getRows();
  const int columns = matrix.getColumns();
  Matrix<decltype(functor(T(), K()))> resultingMatrix(rows, columns);
  for (int i = 0; i < rows; i++) {
    const auto& row = matrix[i];
    for (int j = 0; j < columns; j++) {
      resultingMatrix(i, j) = std::move(functor(row[j], scalar));
    }
  }
  return resultingMatrix;
}

template <typename T, typename K>
auto multiplyMatrices(const Matrix<T>& matrix1, const Matrix<K>& matrix2) 
    -> Matrix<decltype(T() * K())> {
  if (matrix1.getColumns() == matrix2.getRows()) {
    Matrix<decltype(T() + K())> resultingMatrix(matrix1.getRows(), 
                                                matrix2.getColumns());
    for (int i = 0; i < resultingMatrix.getRows(); i++) {
      for (int j = 0; j < resultingMatrix.getColumns(); j++) {
        auto sum = decltype(T() * K())();
        for (int k = 0; k < matrix1.getColumns(); k++) {
          sum += matrix1(i, k) * matrix2(k, j);
        }
        resultingMatrix(i, j) = std::move(sum);
      }
    }
    return resultingMatrix;
  }
  return {};
}

#endif // MATRICES_CPP