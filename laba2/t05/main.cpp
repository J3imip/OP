#include <iostream>

using std::cout;

class Sum {
private:
  int num;
  static int count;
public:
  int getNum() { 
    return this->count; 
  }
  static int getCount() { return count; }

  Sum(int a) {
    num = a;
    count += num;
  }
};

int Sum::count = 0;

int main() {
  Sum n1(1);
  Sum n2(4);
  Sum n3(2);
  Sum n4(6);

  cout << "Result: " << Sum::getCount() << "\n";
}
