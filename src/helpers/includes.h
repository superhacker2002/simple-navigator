#ifndef SRC_INCLUDES_INCLUDES_H_
#define SRC_INCLUDES_INCLUDES_H_

#include "s21_matrix.h"

// note: incase if we wount need anything more
// then matrix - change struct to using
namespace s21 {
struct GraphData {
  Matrix<int> matrix;
  // smth else if needed
};
}  // namespace s21
#endif  // SRC_INCLUDES_INCLUDES_H_