#include "lib.hpp"
#include <iostream>

double f1(double x) {
  return sin(x) / x;
}

template<typename T>
class Func {
private:
  T k;
  T b;
public:
  Func(T k, T b): k(k), b(b) {};
  
  T operator()(T x) const {
    return k * x + b;
  }
};

int main() {
  double x1, x2, step;

  std::cout << "Enter start and end of the interval separated by a space:\n";
  std::cin >> x1 >> x2;
  std::cout << "Enter step: ";
  std::cin >> step;

  Func<double> f2(2, 5);
  std::cout << "\nMinimal root for y=sin(x)/x function: " << getMin(f1, x1, x2, step) << "\n";
  std::cout << "Minimal root for y=2*x+5 function: " << getMin(f2, x1, x2, step);
}
