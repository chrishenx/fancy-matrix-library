#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include <vector>
#include <ostream>
#include <cmath>

/**
 * Monomial struct
 * Model of monomials
 */
template <typename T, typename U>
struct Monomial {
  T coef;
  U exp;
  Monomial() : coef(), exp() {}
  explicit Monomial(const T& coef, const U& exp = U()) : coef(coef), exp(exp) {}
  Monomial(const Monomial& other) : coef(other.coef), exp(other.exp) {}
  template <typename V>
  auto evaluate(const V& value) -> decltype(coef * pow(value, exp)) const {
    return coef * pow(value, exp);
  }
  Monomial operator-() const { return Monomial(-coef, exp); }
  Monomial operator+() const { return *this; }
  Monomial& operator=(const Monomial& other) {
    coef = other.coef;
    exp = other.exp;
    return *this;
  }
  Monomial& operator*=(const Monomial& other) {
    coef *= other.ceof;
    exp += other.exp;
    return *this;
  }
  Monomial operator/=(const Monomial& other) {
    coef /= other.coef;
    exp -= other.exp;
    return *this;
  }
  Monomial& operator*=(const T& coef) {
    this->coef *= coef;
    return *this;
  }
  Monomial& operator/=(const T& coef) {
    this->coef /= coef;
    return *this;
  }
  bool operator<(const Monomial& other) const {
    return other.exp < exp; // It has the inverse meaning
  }
  bool operator==(const Monomial& other) const {
    return exp == other.exp and coef == other.coef;
  }
  static const char VAR = 'x';
};

#include "monomial_operators.h"

/**
 * Polynomial class 
 * Model of polynomials
 */
template <typename T, typename U>
class Polynomial {
 public:
  Polynomial() {}
  Polynomial(const Monomial<T, U>& monomial) : data (1, monomial) {}
  Polynomial(const Polynomial& other) : data (other.data) {}
  Polynomial(Polynomial&& other) : data (std::move(other.data)) {}
  Polynomial(const std::vector<Monomial<T, U>>& mons);
  Polynomial(std::initializer_list<Monomial<T, U>> mons);
  U degree() const { return data.empty() ? U() : data[0].exp; }
  int size() const { return data.size(); }
  
  Polynomial& operator=(const Polynomial& other) { 
    if (this != &other) {
      data = other.data;
    }
    return *this;
  }

  Polynomial& operator=(Polynomial&& other) { 
    if (this != &other) {
      data = std::move(other.data); 
    }
    return *this;
  }
  
  Polynomial operator-() const;
  Polynomial operator+() const { return *this; }

  Polynomial& operator<<(const Monomial<T, U>& monomial);
  Polynomial& operator*=(const Polynomial& other);
  Polynomial& operator*=(const Monomial<T, U>& monomial);
  Polynomial& operator+=(const Polynomial& other);
  Polynomial& operator+=(const Monomial<T, U>& monomial) { 
    return *this << monomial; 
  }
  
  template <typename V>
  auto evaluate(const V& value) -> decltype(T() * pow(value, U())) const;
  
  const std::vector<Monomial<T, U>>& getData() const { return data; }
  typename std::vector<Monomial<T, U>>::const_iterator begin() const { 
    return data.begin(); 
  }
  typename std::vector<Monomial<T, U>>::const_iterator end() const { 
    return data.end(); 
  }
  
  static void group(std::vector<Monomial<T, U>>& data);
 private:
  std::vector<Monomial<T, U>> data;
};

template <typename T, typename U>
Polynomial<T, U> pow(const Polynomial<T, U>& polynomial, int power);

#include "polynomials.cpp"

#endif // POLYNOMIALS_H