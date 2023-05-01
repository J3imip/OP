#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <numeric>

using std::strcpy;
using std::strlen;
using std::ostream;
using std::vector;
using std::cout;
using std::accumulate;

class Group; //prototype of the Group class

class Student {
private: 
  unsigned int id;
  char *surname = nullptr;
  vector<int> grades;
  Group *group = nullptr;
public:
  //copying constructor
  Student(Student &student);
  //constructor with parameters
  Student(unsigned int id, char *surname, vector<int> &grades, Group *group);
  //destructor
  ~Student();

  //setters
  void setId(unsigned int id) { this->id = id; };
  void setSurname(char *surname) {
    if(this->surname != nullptr)
      delete[] this->surname;

    this->surname = new char[strlen(surname) + 1];
    strcpy(this->surname, surname);
  }
  void setGrades(const vector<int> &grades) { this->grades = grades; }
  void setGroup(Group *group) { this->group = group; }

  //getters
  unsigned int getId() { return this->id; }
  char *getSurname() { return this->surname; }
  vector<int> &getGrades() { return this->grades; }
  Group *getGroup() { return this->group; }

  //operators overload
  friend ostream &operator<<(ostream &out, const Student &student);
  Student &operator=(const Student &student);
  bool operator>(const Student &student);
};

Student::Student(Student &student) {
  this->setId(student.id);
  this->setSurname(student.surname);
  this->setGrades(student.grades);
  this->setGroup(student.group);
}

Student::Student(
  unsigned int id, 
  char *surname, 
  vector<int> &grades, 
  Group *group
) {
  this->setId(id);
  this->setSurname(surname);
  this->setGrades(grades);
  this->setGroup(group);
}

Student::~Student() { delete[] surname; }

Student& Student::operator=(const Student &student) {
  if(this == &student) return *this;
  
  this->id = student.id;
  this->group = student.group;

  delete[] this->surname;

  this->surname = new char[strlen(student.surname) + 1];
  strcpy(this->surname, student.surname);

  this->grades = student.grades;

  return *this;
}

bool Student::operator>(const Student &student) {
  return strlen(this->surname) > strlen(student.surname);
}

class Group{
private:
  unsigned int id;
  vector<Student*> students;
public:
  Group();
  Group(unsigned int id, vector<Student*> &students): id(id) {
    this->setStudents(students);
  };

  void find() {
    cout << "\nSEARCH RESULT (grades average 82 – 89):\n";

    for (int st = 0; st < students.size(); st++) {
      vector<int> grades = students[st]->getGrades();
      int average = accumulate(grades.begin(), grades.end(), 0) / grades.size();

      if(average >= 82 && average <= 89) 
        cout << *(this->students[st]);
    }
  }

  void sortBySurnameLength() {
    const int size = students.size();

    for (int i = 0; i < size - 1; i++) {
      for (int j = 0; j < size - i - 1; j++) {
        //usage of overloaded operator>
        if (*(students[j]) > *(students[j+1])) {
          Student *temp = students[j];

          students[j] = students[j+1];
          students[j+1] = temp;
        }
      }
    }
  }

  //setters
  void setId(unsigned int id) { this->id = id; }
  void setStudents(const vector<Student*> &students) {
    this->students = students;

    for (int i = 0; i < students.size(); i++) {
      this->students[i]->setGroup(this);
    }
  }

  //getters
  unsigned int getId() { return this->id; }
  vector<Student*> &getStudents() { return this->students; }

  friend ostream &operator<<(ostream &out, const Group &group) {
    out << "GROUP " << group.id << " INFO:\n";
    for (int i = 0; i < group.students.size(); i++) {
      out << *(group.students[i]);
    }
    return out;
  }

  Student &operator[](int i) {
    return *this->students[i];
  }

  Group &operator=(const Group &group) {
    if(this != &group) {
      this->setStudents(group.students);
    }

    return *this;
  }

};

ostream& operator<<(ostream &out, const Student &student) {
  char buffer[300];
  sprintf(buffer, "\n========(ID:%u)=========\nSurname: %s\nGroup:\t%u\nGrades:\t", 
    student.id, 
    student.surname, 
    student.group->getId()
  );

  for (int i = 0; i < student.grades.size(); i++) {
    if(i != 0) sprintf(buffer + strlen(buffer), ", ");
    sprintf(buffer + strlen(buffer), "%d", student.grades[i]);
  }

  sprintf(buffer + strlen(buffer), "\n");
  out << buffer;
  
  return out;
}

int main() {
  srand(time(NULL));
  const int STUDENTS_COUNT = 5;

  char* surnames[] = {
    (char *)"Kuchma",
    (char *)"Hryhorieva",
    (char *)"Ivaniv",
    (char *)"Konstantyniv",
    (char *)"Esypenko"
  };

  vector<int> grades(4, 100);
  vector<Student*> students;
  students.reserve(STUDENTS_COUNT);

  for (int i = 0; i < STUDENTS_COUNT - 1; i++) {
    students.push_back(new Student(
      rand() % 90000 + 10000, 
      surnames[i], 
      grades, 
      nullptr
    ));
  }

  vector<int> diffGrades = {92, 85, 90, 86};

  //create a student with 82-89 grades average
  students.push_back(new Student(
    rand() % 90000 + 10000, 
    surnames[STUDENTS_COUNT - 1], 
    diffGrades,
    nullptr
  ));

  Group group(rand() % 90000 + 10000, students);
  cout << group;
  
  group.find();
  group.sortBySurnameLength();
  cout << "\nSORT RESULTS:\n\n" << group;
}
