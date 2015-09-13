#include <iostream>
#include <vector>
#include "polynomials.h"

using namespace std;

typedef Polynomial<double, double> DPolynomial;
typedef Monomial<double, double> DMon;

int main () {

  DPolynomial pol = {DMon(1,2), DMon(2,2), DMon(9, -4)};

  cout.precision(10);

  cout << -pol << endl;
  cout << -pol.evaluate(30) << endl;

  return 0;
}