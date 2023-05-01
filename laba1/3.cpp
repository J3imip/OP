#include <iostream>
#include <cstring>

using namespace std;

struct Student {
private:
    unsigned int ID;
    char *lastName;
    int marks[3];
public:
    //setters
    void setID(unsigned int ID) {
        this->ID = ID;
    }
    void setLastName(char *lastName) {
        this->lastName = lastName;
    }
    void setMarks(int marks[3]) {
        for (int i = 0; i < 3; i++) {
            this->marks[i] = marks[i];
            if(marks[i] > 100 || marks[i] < 0) 
                throw "Marks must be between 0 and 100!";
        }
    }

    //getters
    unsigned int getID() {
        return this->ID;
    }
    char *getLastName() {
        return this->lastName;
    }
    int *getMarks() {
        return this->marks;
    }

    void print() {
        cout << "ID: " << this->ID << endl;
        cout << "Last Name: " << this->lastName << endl;
        cout << "Marks: ";
        for (int i = 0; i < 3; i++) {
            cout << this->marks[i] << " ";
        }
    }

    //contructor
    Student(unsigned int ID, char *lastName, int marks[3]) {
        this->setID(ID);
        this->setLastName(lastName);
        this->setMarks(marks);
    }
};

//1
void sort(Student *arr, const int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strlen(arr[j].getLastName()) > strlen(arr[j+1].getLastName())) {
                Student temp = arr[j];
                arr[j].setID(arr[j+1].getID());
                arr[j].setLastName(arr[j+1].getLastName());
                arr[j].setMarks(arr[j+1].getMarks());

                arr[j+1].setID(temp.getID());
                arr[j+1].setLastName(temp.getLastName());
                arr[j+1].setMarks(temp.getMarks());
            }
        }
    }
}

//2
void search(Student *arr, const int size) {
    cout << "===================" << endl;
    for (int i = 0; i < size; i++) {
        double sum = 0, average = 0;
        int *marks = arr[i].getMarks();
        for (int j = 0; j < 3; j++) {
            sum += marks[j];
        }
        average = sum / 3;
        if(average >= 82 && average <= 89) {
            arr[i].print();
            cout << "\n===================" << endl;
        }
    }
}

//3
void printAll(Student *arr, const int size) {
    cout << "==================" << endl;
    for (int i = 0; i < size; i++) {
        arr[i].print();
        cout << "\n==================" << endl;
    }
}

int main() {
    try {
        int marks1[3] = {100, 95, 98};
        int marks2[3] = {100, 95, 100};
        int marks3[3] = {82, 86, 86};

        Student arr[3] = {
            {1, (char*)"Kuchma", marks1},
            {2, (char*)"Konstantyniv", marks2},
            {3, (char*)"Hryhorieva", marks3}
        };

        cout << "Sort results:\n\n";
        sort(arr, 3);
        printAll(arr, 3);

        cout << "\nSearch results:\n\n";
        search(arr, 3);
    } catch (const char* exception) {
        cout << exception << endl;
        return 1;
    }
}
