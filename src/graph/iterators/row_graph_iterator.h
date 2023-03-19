#ifndef ROW_GRAPH_ITERATOR_H_
#define ROW_GRAPH_ITERATOR_H_

#include "graph_iterator.h"

namespace s21 {
template <typename T>
class RowGraphIterator : public GraphIterator<T> {
  friend class Graph;

 public:
  RowGraphIterator() : GraphIterator<T>() {}

  RowGraphIterator(const RowGraphIterator &it) : GraphIterator<T>(it) {}

  ~RowGraphIterator() {}

  RowGraphIterator<T> &operator++() {
    this->curr_col_++;
    return *this;
  }

  RowGraphIterator<T> &operator--() {
    if (this->curr_col_ > 0) {
      this->curr_col_--;
    }
    return *this;
  }

  RowGraphIterator<T> &operator-(int num) {
    for (int i = 0; i < num; i++) {
      --(*this);
    }
    return *this;
  }

  RowGraphIterator<T> &operator+(int num) {
    for (int i = 0; i < num; i++) {
      ++(*this);
    }
    return *this;
  }

 protected:
  RowGraphIterator(s21::Matrix<T> *matrix, int i, int j)
      : GraphIterator<T>(matrix, i, j) {}
};

template <typename T>
class ConstRowGraphIterator : public RowGraphIterator<T> {
  friend class Graph;

 public:
  ConstRowGraphIterator() : RowGraphIterator<T>() {}

  ConstRowGraphIterator(const ConstRowGraphIterator &other)
      : RowGraphIterator<T>(other) {}

  ~ConstRowGraphIterator() {}

  T operator*() { return (*this->matrix_)(this->curr_row_, this->curr_col_); }

 private:
  ConstRowGraphIterator(s21::Matrix<T> *matrix, int i, int j)
      : RowGraphIterator<T>(matrix, i, j) {}
};

}  // namespace s21

#endif  // ROW_GRAPH_ITERATOR_H_
