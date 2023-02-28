#ifndef GRAPH_ITERATOR_H_
#define GRAPH_ITERATOR_H_

#include "../../helpers/s21_matrix.h"

namespace s21 {
template<typename T>
class GraphIterator {
 friend class Graph;
 public:
  GraphIterator() {}
  GraphIterator(const GraphIterator &it) : pointer_(it.pointer_) {}
  ~GraphIterator() {}

  T& operator*() {
    return matrix_(curr_row_, curr_col_);
  }

  bool operator==(const GraphIterator &other) {
    return matrix_ == other.p_data_;
  }

  GraphIterator<T>& operator++() {
    int rows = matrix_.GetRows();
    int cols = matrix_.GetCols();

    if (curr_col_ < cols) {
      curr_col_++;
    } else if (curr_row_ < rows) {
      curr_row_++;
      curr_col_ = 0;
    }

    return *this;
  }

  GraphIterator<T>& operator--() {
    int cols = matrix_.GetCols();

    if (curr_col_ > 0) {
      curr_col_--;
    } else if (curr_row_ > 0) {
      curr_row_--;
      curr_col_ += cols - 1;
    }

    return *this;
  }

 private:
  GraphIterator(s21::Matrix<T> matrix, int i, int j)
    : matrix_(matrix),
    curr_row(i),
    curr_col(j) {}
  
  s21::Matrix<T> matrix_;
  int curr_row_;
  int curr_col_;
};
}  // namespace s21

#endif  // GRAPH_ITERATOR_H_
