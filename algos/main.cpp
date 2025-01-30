#include <iostream>
#include <string>
#include <vector>

#include "func.hpp"

int main(int argc, char **argv)
{
  std::vector<std::string> str_vec{"bravo",           "delta", "bravo", "bravo", "delta",          "alpha",
                                   "delta",           "alpha", "bravo", "delta", "bravo",          "bravo",
                                   "delta",           "alpha", "delta", "alpha", "reallylongword", "impossiblylongword",
                                   "absurdlylongword"};

  std::cout << "Before:" << '\n';
  std::cout << StringVectorToString(str_vec, " ") << '\n';

  std::cout << "Without duplicate words:" << '\n';
  str_vec = EliminateDuplicates(str_vec);
  std::cout << StringVectorToString(str_vec, " ") << "\n";

  std::cout << "Filtered by length:" << '\n';
  str_vec = FilterStringByLength(str_vec, '<', 6);
  std::cout << StringVectorToString(str_vec, " ") << "\n";
  return EXIT_SUCCESS;
}
