#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;


struct LinkedList {
    int value;
    LinkedList *next;
};

//===========UTIL FUNCTIONS===========

void printLinkedList(LinkedList *first) {
    LinkedList *current = first;
    while(current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

void deleteLinkedList(LinkedList *first) {
    LinkedList *current = first;
    while(first) {
        current = first;
        first = first->next;
        delete current;
    }
}

void printArr(int *arr, const int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//================MAIN=================

int main() {
    const int n = 4;
    int elementCounter = 0;
    LinkedList *first = NULL;
    LinkedList *head = NULL;

    ifstream arrIn("arr.txt");
    int value;
    while(arrIn >> value) {
        LinkedList *newLinkedList = new LinkedList;
        newLinkedList->value = value;
        newLinkedList->next = 0;
        if(!first) first = newLinkedList;
        else head->next = newLinkedList;
        head = newLinkedList;
        elementCounter++;
    }

    arrIn.close();

    cout << "Linked list: ";
    printLinkedList(first);

    int m = ceil(double(elementCounter) / double(n));

    int **TDArr = new int*[n];
    for (int i = 0; i < m; i++) {
        TDArr[i] = new int[n];
    }

    LinkedList *current = first;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (current != NULL) {
                TDArr[i][j] = current->value;
                current = current->next;
            }
            else {
                TDArr[i][j] = 0; 
            }
        }
    }

    cout << "\nTwo-dimentional array:" << endl;
    for (int i = 0; i < m; i++) {
        printArr(TDArr[i], n);
    }

    int *maxes = new int[m];
    for (int i = 0; i < m; i++) {
        int max = TDArr[i][0];
        for (int j = 0; j < n; j++) {
            int c = TDArr[i][j];
            TDArr[i][j] = c == 0 ? 1 : c;

            if(c > max && c > 0) max = c;
        }
        maxes[i] = max;
    }

    cout << "\nAffected two-dimentional array:" << endl;
    for (int i = 0; i < m; i++) {
        printArr(TDArr[i], n);
    }

    cout << "\nNatural logarithms of maximal positive elements of rows:" << endl;
    for (int i = 0; i < m; i++) {
        cout << "log(" << maxes[i] << ") = " << log(maxes[i]) << endl;
    }

    deleteLinkedList(first);
    for (int i = 0; i < m; i++) {
        delete[] TDArr[i];
    }
    delete[] TDArr;
    delete[] maxes;
}
