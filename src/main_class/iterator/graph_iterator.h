#ifndef GRAPH_ITERATOR_H_
#define GRAPH_ITERATOR_H_

#include <iterator>

template<typename T>
class GraphIterator: public std::iterator<std::input_iterator_tag, T> {
 friend class Graph;
 public:
   GraphIterator(int line) : pointer_(m_data_(line, 0)) {}
   GraphIterator(T* pointer) : pointer_(pointer) {}

   GraphIterator(const GraphIterator &it) : pointer_(it.pointer_) {}
   bool operator!=(GraphIterator const& other) const {
    return pointer_ != other.pointer_;
   }
   bool operator==(GraphIterator const& other) const {
    return pointer_ == other.pointer_;
   }
   GraphIterator& operator++() {
    ++pointer_;
    return *this;
   }
 private:
   T* pointer_;
};

#endif  // GRAPH_ITERATOR_H_
