#include <iostream>
#include <cstring>

using std::cout;
using std::strcpy;

class Human {
private:
  char name[20];
  int age;
public:
  Human(char *name, int age) {
    strcpy(this->name, name);
    this->age = age;
  }

  virtual void show() {
    cout << "Name: " << name << "\nAge: " << age << "\n";
  }
};

class Citizen : public Human {
private:
  int passportId;
public:
  Citizen(char *name, int age, int passportId):
    Human(name, age), passportId(passportId) {}
  void show() override {
    Human::show();
    cout << "Passport: " << passportId << "\n";
  }
};

class Student : public Citizen {
private:
  int studentId;
public:
  Student(char *name, int age, int passportId, int studentId):
    Citizen(name, age, passportId), studentId(studentId) {}
  void show() override {
    Citizen::show();
    cout << "Student ID: " << studentId << "\n";
  }
};

class Employee : public Citizen {
private:
  char post[20];
public:
  Employee(char *name, int age, int passportId, char *post):
    Citizen(name, age, passportId) {
      strcpy(this->post, post);
    }
  void show() override {
    Citizen::show();
    cout << "Employee post: " << post << "\n";
  }
};

int main() {
  const int size = 4;
  Human *humans[size] = {
    new Human((char *)"Ivaniv", 17),
    new Citizen((char *)"Hryhorieva", 19, 421313),
    new Student((char *)"Konstantyniv", 18, 324253, 22),
    new Employee((char *)"Kuchma", 18, 234636, (char *)"coder")
  };

  for(int i = 0; i < size; i++) {
    humans[i]->show();
    cout << "\n";
    delete humans[i];
  }
}
