#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <initializer_list>
#include <stdexcept>

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::List<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using container_type = Container;

 private:
  container_type container_;

 public:
  // FUNCTIONS
  Stack(const container_type &container = container_type())
      : container_(container) {}
  Stack(const Stack &other) : container_(other.container_) {}
  Stack(std::initializer_list<value_type> const &items) : container_(items) {}
  Stack(Stack &&other) { std::move(other.container_); }
  virtual ~Stack() {}
  Stack &operator=(const Stack &other) {
    container_ = other.container_;
    return *this;
  }
  // ELEMENT ACCESS

  void init() {}
  const_reference top() const { return container_.back(); }
  const_reference peek() const { return container_.back(); }

  // CAPACITY
  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }

  // MODIFIERS
  void push(const_reference data_) { container_.push_back(data_); }
  void pop() { container_.pop_back(); }
  void swap(Stack &other) { container_.swap(other.container_); }
  template <class... Args>
  void emplace_front(Args &&...args) {
    container_.emplace_front(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif  // S21_STACK_H_