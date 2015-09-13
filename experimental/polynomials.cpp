/**
 * @file polynomials.h
 * Polynomial class implementation
 */

#ifndef POLYNOMIALS_CPP
#define POLYNOMIALS_CPP
 
#include <algorithm> 
 
template <typename T, typename U>
std::ostream& operator<<(std::ostream& outputStream, 
    const Polynomial<T, U>& polynomial) {
  outputStream << '(';
  int size = polynomial.size();
  const auto& data = polynomial.getData();
  for (int i = 0; i < size; i++) {
    outputStream << data[i];
    if (i < size - 1) {
      outputStream << ", ";
    }
  }
  outputStream << ')';
  return outputStream;
}
  
template <typename T, typename U>
Polynomial<T, U>::Polynomial(const std::vector<Monomial<T, U>>& mons)
    : data (mons) {
  group(data);
}

template <typename T, typename U>
Polynomial<T, U>::Polynomial(std::initializer_list<Monomial<T, U>> mons)
    : data (mons) {
  group(data);
}

template <typename T, typename U>
Polynomial<T, U> Polynomial<T, U>::operator-() const {
  Polynomial resulting_pol;
  resulting_pol.data.reserve(data.size());
  for (const Monomial<T, U>& mon : data) {
    resulting_pol.data.push_back(-mon);
  }
  return resulting_pol;
}

template <typename T, typename U>
template <typename V> auto Polynomial<T, U>::evaluate(const V& value) 
    -> decltype(T() * pow(value, U())) const {
  decltype(T() * pow(value, U())) result;
  for (const Monomial<T, U>& monomial : data) {
    result += monomial.coef * pow(value, monomial.exp);
  }
  return result;
}

template <typename T, typename U>
void Polynomial<T, U>::group(std::vector<Monomial<T, U>>& data) {
  if (not data.empty()) {
    std::sort(data.begin(), data.end());
    int currentExponent = data[0].exp;
    std::vector<Monomial<T, U>> resulting_polynomial;
    int dataSize = data.size();
    for (int i = 0; i < dataSize; currentExponent--) {
      double coef = 0.0;
      while(data[i].exp == currentExponent) {
        if (i == dataSize)
            break;
        coef += data[i].coef;
        i++;
      }
      if (coef != T()) {
        resulting_polynomial.push_back(Monomial<T, U>(coef, currentExponent));
      }
    }
    data = resulting_polynomial;
  }
}

// this->data exponents: 4 3 1
// input monomial exponent : 2
// Result: this->data exponents: 4 3 2 1   

template <typename T, typename U>
Polynomial<T, U>& Polynomial<T, U>::operator<<(const Monomial<T, U>& monomial) {
  if (not data.empty()) {
    int data_size = data.size();
    bool done = false;
    for (int i = 0; not done and i < data_size; i++) {
      if (data[i].exp == monomial.exp) {
        if (data[i].coef + monomial.coef == T()) {
          data.erase(data.begin() + i);
        } else {
          data[i].coef += monomial.coef;
        }
        done = true;
      } else if (data[i].exp < monomial.exp) {
        data.insert(data.begin() + i, monomial);
        done = true;
      }
    }  
    if (not done) {
      data.push_back(monomial);
    }
  } else {
    data.push_back(monomial);
  }
} 

template <typename T, typename U>
Polynomial<T, U>& Polynomial<T, U>::operator+=(const Polynomial<T, U>& other) {
  data.insert(data.end(), other.begin(), other.end());
  group(data);
  return *this;
}

template <typename T, typename U>
Polynomial<T, U>& Polynomial<T, U>::operator*=(const Polynomial<T, U>& other) {
  const int msize = size();
  const int pol2_size = other.size();
  std::vector<Monomial<T, U>> resulting_data(msize * pol2_size);
  for (int i = 0, k = 0; i < msize; i++) {
    for (int j = 0; j < pol2_size; j++, k++) {
      resulting_data[k] = Monomial<T, U>(data[i].coef * other.data[j].coef, 
                                        data[i].exp + other.data[j].exp);
    }
  }
  group(resulting_data);
  data = resulting_data;
}

template <typename T, typename U>
Polynomial<T, U>& Polynomial<T, U>::operator*=(const Monomial<T, U>& monomial) {
  const int msize = size();
  for (int i = 0; i < msize; i++) {
    data[i].coef *= monomial.coef;
    data[i].exp += monomial.exp;
  }
  return *this;
}

// Operators

template <typename T, typename U>
Polynomial<T, U> operator+(const Polynomial<T, U>& pol1, 
                           const Polynomial<T, U>& pol2) {
  Polynomial<T, U> resulting_polynomial = pol1;
  resulting_polynomial += pol2;
  return resulting_polynomial;
}

template <typename T, typename U>
Polynomial<T, U> operator+(const Polynomial<T, U>& polynomial, 
                           const Monomial<T, U>& monomial) {
  Polynomial<T, U> resulting_polynomial = polynomial;
  resulting_polynomial << monomial;
  return resulting_polynomial;
}

template <typename T, typename U>
Polynomial<T, U> operator+(const Monomial<T, U>& monomial, 
                           const Polynomial<T, U>& polynomial) {
  Polynomial<T, U> resulting_polynomial = polynomial;
  resulting_polynomial << monomial;
  return resulting_polynomial;                                  
}

template <typename T, typename U>
Polynomial<T, U> operator*(const Polynomial<T, U>& pol1, 
                           const Polynomial<T, U>& pol2) {
  Polynomial<T, U> resulting_polynomial = pol1;
  resulting_polynomial *= pol2;
  return resulting_polynomial;
}

template <typename T, typename U>
Polynomial<T, U> operator*(const Polynomial<T, U>& polynomial, 
                           const Monomial<T, U>& monomial) {
  Polynomial<T, U> resulting_polynomial = polynomial;
  resulting_polynomial *= monomial;
  return resulting_polynomial;
}

template <typename T, typename U>
Polynomial<T, U> operator*(const Monomial<T, U>& monomial, 
                           const Polynomial<T, U>& polynomial) {
  Polynomial<T, U> resulting_polynomial = polynomial;
  resulting_polynomial *= monomial;
  return resulting_polynomial;                                  
}

template <typename T, typename U>
Polynomial<T, U> pow(const Polynomial<T, U>& polynomial, int power) {
  Polynomial<T, U> resulting_polynomial = polynomial;
  for (int i = 1; i < power; i++){
      resulting_polynomial *= polynomial;
  }
  return resulting_polynomial;
}

#endif // POLYNOMIALS_CPP