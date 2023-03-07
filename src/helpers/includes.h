#ifndef SRC_INCLUDES_INCLUDES_H_
#define SRC_INCLUDES_INCLUDES_H_

#include "s21_matrix.h"
#include "memory"

// note: incase if we wount need anything more
// then matrix - change struct to using
namespace s21 {
struct GraphData {
  using MatrixType = Matrix<double>;
  void operator= (const GraphData& other) {
    matrix = std::make_unique<MatrixType>(*other.matrix);
  }
  GraphData() {}
  GraphData(const GraphData& other) {
    matrix = std::make_unique<MatrixType>(*other.matrix);
  }
  std::unique_ptr<MatrixType> matrix;
  // smth else if needed
};
}  // namespace s21
#endif  // SRC_INCLUDES_INCLUDES_H_