#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>

template<typename T>
void swap_elements(T& element1, T& element2) {
  T temp = element1;
  element1 = element2;
  element2 = temp;
}

template<typename T>
void swap_array_elements(T* array, int index1, int index2) {
  swap_elements(array[index1], array[index2]);
}

template<typename T>
int find_element(T* array, int size, T value) {
  for (int i = 0; i < size; i++) {
    if (array[i] == value) {
      return i;
    }
  }
  return -1;
}

template<typename T>
void swap_adjacent_elements(T* array, int size) {
  for (int i = 0; i < size - 1; i += 2) {
    swap_elements(array[i], array[i + 1]);
  }
}

#endif // LIB_HPP

