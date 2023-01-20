#include "FileHandler.h"
#include <iostream>

int main() {
  s21::FileHandler handler;
  auto data = handler.ParseFile("smth.txt");
  for (int i = 0; i < data.matrix.GetCols(); ++i) {
    for (int j = 0; j < data.matrix.GetRows(); ++j) {
      std::cout << data.matrix.at(i, j) << " ";
    }
    std::cout << std::endl;
  }
  return 0;

}