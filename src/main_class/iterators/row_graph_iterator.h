#ifndef ROW_GRAPH_ITERATOR_H_
#define ROW_GRAPH_ITERATOR_H_

#include "graph_iterator.h"

namespace s21 {
template<typename T>
class RowGraphIterator : public GraphIterator<T> {
 friend class Graph;
 public:
  RowGraphIterator() : GraphIterator<T>() {}

  RowGraphIterator(const RowGraphIterator &it)
    : GraphIterator<T>(it) {}

  ~RowGraphIterator() {}

  RowGraphIterator<T>& operator++() {
    this->curr_col_++;
    return *this;
  }

  RowGraphIterator<T>& operator--() {
    if (this->curr_col_ > 0) {
      this->curr_col_--;
    }
    return *this;
  }

  RowGraphIterator<T>& operator-(int num) {
    for (int i = 0; i < num; i++) {
      --(*this);
    }
    return *this;
  }

  RowGraphIterator<T>& operator+(int num) {
    for (int i = 0; i < num; i++) {
      ++(*this);
    }
    return *this;
  }

 private:
  RowGraphIterator(s21::Matrix<T>* matrix, int i, int j)
    : GraphIterator<T>(matrix, i, j) {}
};
}  // namespace s21

#endif  // ROW_GRAPH_ITERATOR_H_
