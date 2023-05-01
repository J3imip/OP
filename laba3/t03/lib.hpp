#ifndef LIB_HPP
#define LIB_HPP

#include <cmath>

template<typename Func>
double getMin(Func f, double x1, double x2, double step) {
  double min = f(x1);
  for(int i = x1; i <= x2; i += step) {
    double y = f(i);

    if(min > y) min = y;
  } 
  
  return min;
}

#endif // !LIB_HPP
