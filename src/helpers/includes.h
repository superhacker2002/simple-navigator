#ifndef SRC_INCLUDES_INCLUDES_H_
#define SRC_INCLUDES_INCLUDES_H_

#include "s21_matrix.h"
#include "memory"

// note: incase if we wount need anything more
// then matrix - change struct to using
namespace s21 {
struct GraphData {
  void operator= (const GraphData& other) {
    matrix = std::make_unique<Matrix<int>>(*other.matrix);
  }
  GraphData() {}
  GraphData(const GraphData& other) {
    matrix = std::make_unique<Matrix<int>>(*other.matrix);
  }
  std::unique_ptr<Matrix<int>> matrix;
  // smth else if needed
};
}  // namespace s21
#endif  // SRC_INCLUDES_INCLUDES_H_