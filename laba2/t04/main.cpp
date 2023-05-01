#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::vector;

class IntArray {
  friend ostream& operator<<(ostream& out, const IntArray& a);
  friend istream& operator>>(istream& in, IntArray& a);
  
  //using template to avoid huge amount of boilerplate code
  template<typename Op>
  friend IntArray applyOperator(const IntArray &a1, const IntArray& a2, char *buffer, Op op);

  friend IntArray operator+(const IntArray &a1, const IntArray& a2) {
    char buffer[100];
    sprintf(buffer, "Sum result:\n");
    return applyOperator(a1, a2, buffer, std::plus<int>());
  };
  friend IntArray operator-(const IntArray &a1, const IntArray& a2) {
    char buffer[100];
    sprintf(buffer, "Subtraction result:\n");
    return applyOperator(a1, a2, buffer, std::minus<int>());
  };
  friend IntArray operator*(const IntArray &a1, const IntArray& a2);
private:
  vector<vector<int>>* array;
public:
  class OutOfBounds {
    int index;
  public:
    OutOfBounds(int i): index(i) {}
    int getIndex() { return this->index; }
  };
  
  class SizeMismatch : public std::exception {
  public:
    const char* what() const noexcept override {
      return "Matrix dimensions do not match for operation!";
    }
  };

  IntArray() {}
  IntArray(int n, int m) {
    if(n <= 0 || m <= 0) 
      throw OutOfBounds(n <= 0 ? n : m);

    this->array = new vector<vector<int>>(n, vector<int>(m));
  }

  void addElem(int elem);
  vector<int>& operator[](int index);

  vector<vector<int>>* getArray() { return this->array; }
};

template<typename Op>
IntArray applyOperator(const IntArray &a1, const IntArray& a2, char *buffer, Op op) {
  if(
    (*a1.array).size() != (*a2.array).size() ||
    (*a1.array)[0].size() != (*a2.array)[0].size()
  ) {
    throw IntArray::SizeMismatch();
  }

  cout << buffer;

  IntArray result(a1.array->size(), (*a1.array)[0].size());

  for (int i = 0; i < a1.array->size(); i++) {
    for (int j = 0; j < (*a1.array)[i].size(); j++) {
      result[i][j] = op((*a1.array)[i][j], (*a2.array)[i][j]);
    }
  }

  return result;
}

IntArray operator*(const IntArray& a1, const IntArray& a2) {
  if((*a1.array)[0].size() != a2.array->size()) {
    throw IntArray::SizeMismatch();
  }

  cout << "Multiply result:\n";
  IntArray result(a1.array->size(), (*a2.array)[0].size());

  for (int i = 0; i < a1.array->size(); i++) {
    for (int j = 0; j < (*a2.array)[0].size(); j++) {
      for (int k = 0; k < (*a1.array)[0].size(); k++) {
        result[i][j] += (*a1.array)[i][k] * (*a2.array)[k][j];
      }
    }
  }

  return result;
}

ostream& operator<<(ostream& out, const IntArray& a) {
  for (vector<int> row : *a.array) {
    for (int el : row) {
      out << el << " ";
    }

    out << "\n";
  }

  return out;
}

istream& operator>>(istream& in, IntArray& a) {
  cout << "Enter elements of 2D array.\n";
  for (int i = 0; i < a.array->size(); i++) {
    cout << "Enter row: ";
    for (int j = 0; j < (*a.array)[i].size(); j++) {
      in >> (*a.array)[i][j];
    }
  }

  cout << "\n";

  return in;
}

vector<int>& IntArray::operator[](int index) {
  if(index < 0 || index >= this->array->size()) 
    throw OutOfBounds(index);

  return (*this->array)[index];
}

void replaceZeros(IntArray &a) {
  vector<vector<int>> *arr = a.getArray();
  for (int i = 0; i < arr->size(); i++) {
    for (int j = 0; j < (*arr)[i].size(); j++) {
      if((*arr)[i][j] == 0) (*arr)[i][j] = 1;
    }
  }
}

int main() {
  IntArray a1(2, 2);
  IntArray a2(2, 2);

  cin >> a1;
  cin >> a2;

  try {
    cout << a1 + a2;
    cout << a1 - a2;
    cout << a1 * a2;
  } catch (const IntArray::SizeMismatch &e) {
    cout << e.what();
  }

  try {
    cout << a1[2][2];
  } catch (IntArray::OutOfBounds &e) {
    cout << "\nIndex " << e.getIndex() << " is out of bounds!\n\n";
  }

  replaceZeros(a1);
  cout << "Replaced zeros in first matrix:\n" << a1;
}
