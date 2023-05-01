#include <iostream>
#include <string>
#include "lib.hpp"

int main() {
  int int_array[] = {10, 20, 30, 40, 50};
  int int_array_size = sizeof(int_array) / sizeof(int_array[0]);

  swap_array_elements(int_array, 1, 3);
  std::cout << "Int array after swapping elements: ";
  for (int i = 0; i < int_array_size; i++) {
      std::cout << int_array[i] << " ";
  }

  int search_value = 20;
  int search_result = find_element(int_array, int_array_size, search_value);
  std::cout << "\nSearch result for value " << search_value << ": " << search_result << std::endl;

  swap_adjacent_elements(int_array, int_array_size);
  std::cout << "Int array after swapping adjacent elements: ";
  for (int i = 0; i < int_array_size; i++) {
      std::cout << int_array[i] << " ";
  }

  std::cout << std::endl;
}
