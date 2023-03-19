#ifndef COL_GRAPH_ITERATOR_
#define COL_GRAPH_ITERATOR_

#include "graph_iterator.h"

namespace s21 {
template <typename T>
class ColGraphIterator : public GraphIterator<T> {
  friend class Graph;

 public:
  ColGraphIterator() : GraphIterator<T>() {}

  ColGraphIterator(const ColGraphIterator &it) : GraphIterator<T>(it) {}

  ~ColGraphIterator() {}

  ColGraphIterator<T> &operator++() {
    this->curr_row_++;
    return *this;
  }

  ColGraphIterator<T> &operator--() {
    if (this->curr_row_ > 0) {
      this->curr_row_--;
    }
    return *this;
  }

  ColGraphIterator<T> &operator-(int num) {
    for (int i = 0; i < num; i++) {
      --(*this);
    }
    return *this;
  }

  ColGraphIterator<T> &operator+(int num) {
    for (int i = 0; i < num; i++) {
      ++(*this);
    }
    return *this;
  }

 protected:
  ColGraphIterator(s21::Matrix<T> *matrix, int i, int j)
      : GraphIterator<T>(matrix, i, j) {}
};

template <typename T>
class ConstColGraphIterator : public ColGraphIterator<T> {
  friend class Graph;

 public:
  ConstColGraphIterator() : ColGraphIterator<T>() {}

  ConstColGraphIterator(const ConstColGraphIterator &it)
      : ColGraphIterator<T>(it) {}

  ~ConstColGraphIterator() {}

  T operator*() { return (*this->matrix_)(this->curr_row_, this->curr_col_); }

 private:
  ConstColGraphIterator(s21::Matrix<T> *matrix, int i, int j)
      : ColGraphIterator<T>(matrix, i, j) {}
};

}  // namespace s21

#endif  // COL_GRAPH_ITERATOR_
