#include "base.h"
#include <iostream>

void BaseClass::calc(double x1, double x2, double step) {
  double min = function(x1);
  for(int i = x1; i <= x2; i += step) {
    double y = function(i);

    if(min > y) min = y;
  } 
  
  std::cout << "Minimal root: " << min;
}
