#ifndef BASE_H
#define BASE_H

class BaseClass {
public:
  void calc(double x1, double x2, double step);
  virtual double function(double x) = 0;
};

#endif
