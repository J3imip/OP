#include "fraction.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::vector;

template <typename T>
class IntArray2D {
  friend ostream& operator<<(ostream& out, const IntArray2D& a) {
    for (int i = 0; i < a.array->size(); i++) {
      for (int j = 0; j < (*a.array)[i].size(); j++) {
        out << (*a.array)[i][j] << " ";
      }
      out << std::endl;
    }
    return out;
  }
  friend istream& operator>>(istream& in, IntArray2D& a) {
    cout << "Enter elements of 2D array.\n";
    for (int i = 0; i < a.array->size(); i++) {
      cout << "Enter row: ";
      for (int j = 0; j < (*a.array)[i].size(); j++) {
        in >> (*a.array)[i][j];
        if(in.fail()) {
          throw std::invalid_argument("Input must be a digit!");
        }
      }
    }

    cout << "\n";

    return in;
  }

private:
  vector<vector<T>>* array;

public:
  IntArray2D() {}
  IntArray2D(int n, int m) {
    if (n <= 0 || m <= 0)
      throw std::invalid_argument("Array size should be positive");

    this->array = new vector<vector<T>>(n, vector<T>(m));
  }

  vector<T>& operator[](int index) { return (*array)[index]; }
  vector<vector<T>>* getArray() { return this->array; }

  T getMin() {
    T min = (*array)[0][0];
    for (int i = 0; i < array->size(); i++) {
      for (int j = 0; j < (*array)[i].size(); j++) {
        if ((*array)[i][j] < min) {
          min = (*array)[i][j];
        }
      }
    }
    return min;
  }

  void replaceZeros() {
    for (int i = 0; i < array->size(); i++) {
      for (int j = 0; j < (*array)[i].size(); j++) {
        if ((*array)[i][j] == 0) {
          (*array)[i][j] = 1;
        }
      }
    }
  }
};

template <typename T>
T getMin(const IntArray2D<T>& a) {
  return a.getMin();
}

int main() {
  IntArray2D<int> ia1(2, 2);
  IntArray2D<double> ia2(2, 2);
  IntArray2D<Fraction> ia3(2, 2);
  
  try {
    cout << "Enter matrix of integers:\n";
    cin >> ia1;

    cout << "Enter matrix of doubles:\n";
    cin >> ia2;

    cout << "Enter matrix of fractions:\n";
    cin >> ia3;
  } catch (std::invalid_argument &e) {
    cout << e.what();
    return 1;
  }

  cout << "Min of 1st matrix: "<< ia1.getMin() << "\n";
  cout << "Min of 2st matrix: "<< ia2.getMin() << "\n";
  cout << "Min of 3st matrix: "<< ia3.getMin() << "\n";

  ia1.replaceZeros();
  ia2.replaceZeros();

  
  vector<vector<Fraction>> *arr = ia3.getArray();
  for (int i = 0; i < arr->size(); i++) {
    for (int j = 0; j < (*arr)[i].size(); j++) {
      if((*arr)[i][j].getDouble() == 0) {
        (*arr)[i][j].setNumerator(1);
        (*arr)[i][j].setDenominator(1);
      }
    }
  }

  cout << "Affected arrays:\n";
  cout << "\nIntegers:\n";
  cout << ia1;

  cout << "\nDoubles:\n";
  cout << ia2;

  cout << "\nFractions:\n";
  cout << ia3;
}
