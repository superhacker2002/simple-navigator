#ifndef INCLUDES_H_
#define INCLUDES_H_

#include "s21_matrix.h"

#include <memory>

// note: incase if we wount need anything more
// then matrix - change struct to using
namespace s21 {
struct GraphData {
  using MatrixType = Matrix<double>;
  void operator=(const GraphData& other) {
    matrix = std::make_unique<MatrixType>(*other.matrix);
  }
  GraphData() {}
  GraphData(const GraphData& other) {
    matrix = std::make_unique<MatrixType>(*other.matrix);
  }
  std::unique_ptr<MatrixType> matrix;
  // smth else if needed
};

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

}  // namespace s21
#endif  // INCLUDES_H_