#ifndef GRAPH_ITERATOR_H_
#define GRAPH_ITERATOR_H_

#include "../../helpers/s21_matrix.h"

namespace s21 {
template <typename T>
class GraphIterator {
  friend class Graph;

 public:
  GraphIterator() : matrix_(nullptr), curr_row_(0), curr_col_(0) {}

  GraphIterator(const GraphIterator& it)
      : matrix_(it.matrix_), curr_row_(it.curr_row_), curr_col_(it.curr_col_) {}

  ~GraphIterator() {}

  T& operator*() { return (*matrix_)(curr_row_, curr_col_); }

  bool operator==(const GraphIterator& other) {
    return matrix_ == other.matrix_ && curr_row_ == other.curr_row_ &&
           curr_col_ == other.curr_col_;
  }

  bool operator!=(const GraphIterator& other) {
    return matrix_ != other.matrix_ || curr_row_ != other.curr_row_ ||
           curr_col_ != other.curr_col_;
  }

  GraphIterator<T>& operator++() {
    int rows = (*matrix_).GetRows();
    int cols = (*matrix_).GetCols();
    if (curr_col_ < cols - 1) {
      curr_col_++;
    } else if (curr_col_ == cols - 1 && curr_row_ == rows - 1) {
      curr_col_++;
    } else if (curr_row_ < rows) {
      curr_row_++;
      curr_col_ = 0;
    }
    return *this;
  }

  GraphIterator<T>& operator--() {
    int cols = (*matrix_).GetCols();
    if (curr_col_ > 0) {
      curr_col_--;
    } else if (curr_row_ > 0) {
      curr_row_--;
      curr_col_ += cols - 1;
    }
    return *this;
  }

  GraphIterator<T>& operator-(int num) {
    for (int i = 0; i < num; i++) {
      --(*this);
    }
    return *this;
  }

  GraphIterator<T>& operator+(int num) {
    for (int i = 0; i < num; i++) {
      ++(*this);
    }
    return *this;
  }
  int get_curr_row() { return curr_row_; }
  int get_curr_col() { return curr_col_; }

 protected:
  GraphIterator(s21::Matrix<T>* matrix, int i, int j)
      : matrix_(matrix), curr_row_(i), curr_col_(j) {}

  s21::Matrix<T>* matrix_;
  int curr_row_;
  int curr_col_;
};

template <typename T>
class ConstGraphIterator : public GraphIterator<T> {
  friend class Graph;
  public:
    ConstGraphIterator() : GraphIterator<T>() {}

    ConstGraphIterator(const ConstGraphIterator& other) : GraphIterator<T>(other) {}

    ~ConstGraphIterator() {}

    T operator*() { return (*this->matrix_)(this->curr_row_, this->curr_col_); }

  private:
    ConstGraphIterator(s21::Matrix<T>* matrix, int i, int j)
      : GraphIterator<T>(matrix, i, j) {}

};

}  // namespace s21

#endif  // GRAPH_ITERATOR_H_
