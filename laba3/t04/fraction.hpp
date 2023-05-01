#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
using std::cout;
using std::istream;
using std::ostream;
using std::invalid_argument;

class Fraction {
  //input operator
  friend istream &operator>>(istream &input, Fraction &frac) {
    cout << "Enter a fraction in n/d form: ";
    char slash;
    input >> frac.numerator >> slash >> frac.denominator;

    if(frac.denominator == 0) 
      throw invalid_argument("Error: denominator cannot be a zero.\n");
    
    frac.reduce();
    return input;
  }
  //output operator
  friend ostream &operator<<(ostream &output, Fraction frac) {
    if(frac.numerator == 0) output << 0;
    else if(frac.denominator == 1) output << frac.numerator;
    else if(abs(frac.denominator) == abs(frac.numerator)) {
      if(frac.numerator - frac.denominator == 0) 
        output << 1;
      else if(frac.numerator + frac.denominator == 0) 
        output << -1;
    }
    else if(abs(frac.numerator) > abs(frac.denominator)) {
      int intPart = frac.numerator / frac.denominator;
      int newNumerator = frac.numerator - frac.denominator * intPart;

      if(intPart < 0) {
        newNumerator = abs(newNumerator);
        frac.denominator = abs(frac.denominator);
      }

      if(newNumerator == 0) 
        output << intPart;
      else
        output << intPart << " " << newNumerator << "/" << frac.denominator;
    }
    else {
      output << frac.numerator << "/" << frac.denominator;
    }
    
    return output;
  }

  //calculate operators
  friend Fraction operator+(Fraction frac1, Fraction frac2) {
    int resultNumerator = frac1.numerator * frac2.denominator 
      + frac2.numerator * frac1.denominator;
    int resultDenominator = frac1.denominator * frac2.denominator;

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduce();
    return result;
  }
  friend Fraction operator-(Fraction frac1, Fraction frac2) {
    int resultNumerator = frac1.numerator * frac2.denominator 
      - frac2.numerator * frac1.denominator;
    int resultDenominator = frac1.denominator * frac2.denominator;

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduce();
    return result;
  }
  friend Fraction operator/(Fraction frac1, Fraction frac2) {
    int resultNumerator = frac1.numerator * frac2.denominator;
    int resultDenominator = frac1.denominator * frac2.numerator;

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduce();
    return result;
  }
  friend Fraction operator*(Fraction frac1, Fraction frac2) {
    int resultNumerator = frac1.numerator * frac2.numerator;
    int resultDenominator = frac1.denominator * frac2.denominator;

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduce();
    return result;
  }
  friend bool operator<(Fraction frac1, Fraction frac2) {
      return (frac1.numerator * frac2.denominator < frac2.numerator * frac1.denominator);
  }
  friend bool operator>(Fraction frac1, Fraction frac2) {
      return (frac1.numerator * frac2.denominator > frac2.numerator * frac1.denominator);
  }
  friend bool operator<=(Fraction frac1, Fraction frac2) {
      return (frac1.numerator * frac2.denominator <= frac2.numerator * frac1.denominator);
  }
  friend bool operator>=(Fraction frac1, Fraction frac2) {
      return (frac1.numerator * frac2.denominator >= frac2.numerator * frac1.denominator);
  }
private:
  int numerator, denominator;
public:
  Fraction() {}
  Fraction(int n, int d): numerator(n), denominator(d) {}

  int getNumerator() {
    return this->numerator;
  }

  int getDenominator() {
    return this->denominator;
  }

  void setNumerator(int numerator) {
    this->numerator = numerator;
  }

  void setDenominator(int denominator) {
    this->denominator = denominator;
  }

  void reduce() {
    int gcd = findGCD(this->numerator, this->denominator);
    numerator /= gcd;
    denominator /= gcd;
  }
  //finds greatest common divisor
  int findGCD(int a, int b) {
      if (b == 0) return a;
      return findGCD(b, a % b);
  }

  double getDouble() {
    return double(numerator)/double(denominator);
  }
};

#endif // !FRACTION_H
