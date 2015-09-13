#ifndef MONOMIAL_OPERATORS_H
#define MONOMIAL_OPERATORS_H

#include <ostream>

template <typename T, typename U>
class Polynomial;

template <typename T, typename U>
std::ostream& operator<<(std::ostream& outputStream, 
    const Monomial<T, U>& monomial) {
  outputStream << monomial.coef;
  if (monomial.exp != U()) {
    outputStream << "x^" << monomial.exp;
  }
  return outputStream;
}

template <typename T, typename U>
inline Polynomial<T, U> operator-(const Monomial<T, U>& mon1, 
    const Monomial<T, U>& mon2) {
  return {mon1, -mon2};
}

template <typename T, typename U>
inline Polynomial<T, U> operator-(const Monomial<T, U>& monomial, 
    const T& coef) {
  return {monomial, -Monomial<T, U>(coef, U())};
}

template <typename T, typename U>
inline Polynomial<T, U> operator-(const T& coef, 
    const Monomial<T, U>& monomial) {
  return {Monomial<T, U>(coef, U()), -monomial};
}

template <typename T, typename U>
inline Polynomial<T, U> operator+(const Monomial<T, U>& mon1, 
    const Monomial<T, U>& mon2) {
  return {mon1, mon2};
}

template <typename T, typename U>
inline Polynomial<T, U> operator+(const Monomial<T, U>& monomial, 
    const T& coef) {
  return {monomial, Monomial<T, U>(coef, U())};
}

template <typename T, typename U>
inline Polynomial<T, U> operator+(const T& coef, 
    const Monomial<T, U>& monomial) {
  return {monomial, Monomial<T, U>(coef, U())};
}

template <typename T, typename U>
inline Monomial<T, U> operator*(const Monomial<T, U>& mon1, 
    const Monomial<T, U>& mon2) {
  return Monomial<T, U>(mon1) *= mon2;
}

template <typename T, typename U>
inline Monomial<T, U> operator*(const Monomial<T, U>& monomial, 
    const T& coef) {
  return Monomial<T, U>(monomial) *= coef;
}

template <typename T, typename U>
inline Monomial<T, U> operator*(const T& coef, 
    const Monomial<T, U>& monomial) {
  return Monomial<T, U>(monomial) *= coef;
}

template <typename T, typename U>
inline Monomial<T, U> operator/(const Monomial<T, U>& mon1, 
    const Monomial<T, U>& mon2) {
  return Monomial<T, U>(mon1) /= mon2;
}

template <typename T, typename U>
inline Monomial<T, U> operator/(const Monomial<T, U>& monomial, 
    const T& coef) {
  return Monomial<T, U>(monomial) /= coef;
}

template <typename T, typename U>
inline Monomial<T, U> operator/(const T& coef, 
    const Monomial<T, U>& monomial) {
  return Monomial<T, U>(coef) /= monomial;
}

#endif // MONOMIAL_OPERATORS_H