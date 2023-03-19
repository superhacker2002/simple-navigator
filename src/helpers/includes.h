#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <memory>
#include <vector>

#include "s21_matrix.h"

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
};

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

using VerticesList = std::vector<int>;
constexpr double INF = std::numeric_limits<double>::infinity();
}  // namespace s21
#endif  // INCLUDES_H_