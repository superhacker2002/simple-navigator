#ifndef GRAPH_ITERATOR_H_
#define GRAPH_ITERATOR_H_

#include <iterator>

template<typename T>
class GraphIterator: public std::iterator<std::input_iterator_tag, T> {
 friend class Graph;
 private:
  GraphIterator(ValueType* p);
 public:
   GraphIterator(const GraphIterator &it); 
   bool operator!=(GraphIterator const& other) const;
   bool operator==(GraphIterator const& other) const;
   typename GraphIterator::reference operator*() const;
   GraphIterator& operator++();
 private:
   T* pointer_;
};

#endif  // GRAPH_ITERATOR_H_
