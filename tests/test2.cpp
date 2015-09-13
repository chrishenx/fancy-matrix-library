#include <iostream>
#include "matrices.h"

using namespace std;

typedef Matrix<double> Doubles;

int main() {

  Doubles miDoubles = {{1,2,4}, {20,-10, 1}};
  
  cout << miDoubles << endl;
  
  cout << 1 / miDoubles << endl;

  return 0;
}