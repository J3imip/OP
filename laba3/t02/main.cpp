#include "base.h"
#include <iostream>
#include <cmath>

class DerivedClass : public BaseClass {
public:
  double function(double x) override {
    return sin(x) / x;
  }
};

int main() {
  DerivedClass d;
  double x1, x2, step;

  std::cout << "Enter start and end of the interval separated by a space:\n";
  std::cin >> x1 >> x2;
  std::cout << "Enter step: ";
  std::cin >> step;

  d.calc(x1, x2, step);
}
