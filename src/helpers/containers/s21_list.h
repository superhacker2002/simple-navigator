#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <stdexcept>

#include "list_iterator.h"
#include "s21_node.h"

namespace s21 {
template <typename T, class Allocator = std::allocator<T>>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using node_pointer = Node<value_type> *;
  using node_type = Node<value_type>;
  using iterator = ListIterator<value_type>;
  using const_iterator = ConstListIterator<T>;
  using allocator_type = Allocator;
  using allocator_rebind = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<node_type>;
  using size_type = size_t;

 private:
  size_type size_;
  node_pointer head_;
  node_pointer end_;
  allocator_type allocator_;
  allocator_rebind alloc_rebind_;

 public:
  // FUNCTIONS
  List(const allocator_type &Alloc = allocator_type())
      : size_(0), head_(nullptr), allocator_(Alloc) {
    make_end();
  }

  List(size_type n, const_reference val = value_type(),
       const allocator_type &Alloc = allocator_type())
      : size_(0), head_(nullptr), allocator_(Alloc) {
    make_end();
    assign(n, val);
  }

  List(std::initializer_list<value_type> const &items) : List() {
    auto start = items.begin();
    auto end = items.end();
    while (start != end) {
      push_back(*start);
      start++;
    }
  }

  List(const List &other) : List() {
    if (!other.empty()) {
      assign(other.begin(), other.end());
    }
  }

  List(List &&other)
      : size_(other.size_), head_(other.head_), end_(other.end_) {
    other.head_ = nullptr;
    other.end_ = nullptr;
    other.size_ = 0;
  }

  virtual ~List() {
    clear();
    if (end_) {
      kill_node(end_);
    }
  }

  List &operator=(const List &other) {
    clear();
    kill_node(end_);
    end_ = make_node(value_type());
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
    return *this;
  }

  // ELEMENT ACCESS

  const_reference front() const { return *(head_->data()); }

  const_reference back() const {
    if (size_ > 0) {
      return *(end_->prev()->data());
    } else {
      return *(end_->data());
    }
  }

  // IERATORS

  iterator begin() const { return iterator(head_); }
  iterator end() const { return iterator(end_); }

  const_iterator cbegin() const { return const_iterator(head_); }
  const_iterator cend() const { return const_iterator(end_); }

  // CAPACITY
  bool empty() const { return size_ == 0; }

  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept { return allocator_.max_size(); }

  // MODIFIERS

  void clear() {
    if (head_) {
      for (auto it = begin(); it != end(); ++it) {
        kill_node(it.base());
      }
      head_ = nullptr;
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    iterator it_inserted;
    if (pos == begin()) {
      push_front(value);
      it_inserted = begin();
    } else if (pos == end()) {
      push_back(value);
      it_inserted = end_->prev();
    } else {
      node_pointer new_node = make_node(value);
      new_node->insert_before_node(pos.base());
      ++size_;
      it_inserted = iterator(new_node);
    }
    return it_inserted;
  }

  void erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
    } else if (pos == end()) {
      pop_back();
    } else {
      pos.base()->connect_sides_nodes();
      kill_node(pos.base());
      --size_;
    }
  }

  void erase(iterator first, iterator last) {
    while (first != last) erase(first);
    ++first;
  }

  void push_back(const_reference value) {
    node_pointer new_node = make_node(value);
    new_node->insert_before_node(end_);
    if (size_ == 0) {
      head_ = new_node;
    }
    ++size_;
  }

  void pop_back() {
    if (size_ == 1) {
      pop_front();
    } else if (size_ > 1) {
      node_pointer tmp = end_->prev();
      end_->prev()->connect_sides_nodes();
      kill_node(tmp);
      --size_;
    }
  }
  void push_front(value_type value) {
    node_pointer new_node = make_node(value);
    if (size_ == 0) {
      new_node->insert_before_node(end_);
    } else {
      new_node->insert_before_node(head_);
    }
    head_ = new_node;
    size_++;
  }

  void pop_front() {
    if (size_ == 1) {
      kill_node(head_);
      head_ = end_;
      end_->prev() = nullptr;
    } else if (size_ > 1) {
      node_pointer tmp = head_->next();
      kill_node(head_);
      head_ = tmp;
    }
    --size_;
  }

  void swap(List &other) {
    List tmp(other);
    other = *this;
    *this = tmp;
  }

  void merge(List &other) {
    if (&other != this) {
      if (size_ == 0) {
        assign(other.begin(), other.end());
        other.clear();
      } else {
        iterator first_1 = begin();
        iterator end_1 = end();
        iterator first_2 = other.begin();
        iterator end_2 = other.end();

        while (first_1 != end_1 && first_2 != end_2) {
          if (*first_2 <= *first_1) {
            other.head_ = first_2.base()->next();
            --other.size_;
            first_2.base()->connect_sides_nodes();
            first_2.base()->insert_before_node(first_1.base());

            if (first_1 == begin()) {
              head_ = head_->prev();
            }
            ++size_;
            first_2 = other.begin();
          } else {
            ++first_1;
          }
        }
      }
    }
  }

  void splice(iterator pos, List &other) {
    other.end_->prev()->next() = pos.base();
    if (pos == begin()) {
      head_ = other.head_;
    } else {
      pos.base()->prev()->next() = other.head_;
      pos.base()->prev() = other.end_->prev();
    }
    size_ += other.size_;
    other.size_ = 0;
    other.loop();
  }

  void reverse() noexcept {
    if (size_ > 1) {
      node_pointer head = end_->prev();
      auto it = begin();
      node_pointer current_node = it.base();
      node_pointer tmp;

      for (size_type i = 0; i < size_; i++) {
        tmp = current_node->next();
        if (i == 0) {
          current_node->next() = end_;
        } else {
          current_node->next() = current_node->prev();
        }
        current_node->prev() = tmp;
        current_node = current_node->prev();
      }
      head_ = head;
    }
  }

  void unique() {
    iterator prev = begin();
    iterator next = prev;
    iterator last = end();
    while (next != last) {
      ++next;
      if (*prev == *next) {
        erase(next);
        next = prev;
      } else {
        prev = next;
      }
    }
  }

  void sort() {
    if (size_ > 0) {
      head_ = merge_sort(head_);
    }
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(const_cast<node_pointer>(pos.base()));
    return insert(it, value_type(std::forward<Args>(args)...));
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    push_back(value_type(std::forward<Args>(args)...));
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    push_front(value_type(std::forward<Args>(args)...));
  }

 private:
  node_pointer make_end() {
    end_ = make_node(value_type());
    loop();
    return end_;
  }

  void loop() {
    head_ = end_;
    end_->prev() = nullptr;
    end_->next() = nullptr;
  }

  void assign(iterator start, iterator end) {
    clear();
    while (start != end) {
      push_back(*start);
      ++start;
    }
  }

  void assign(size_type size, const_reference val) {
    clear();
    for (size_type i = 0; i < size; i++) {
      push_back(val);
    }
  }

  node_pointer make_node(const_reference val) {
    node_pointer new_node = alloc_rebind_.allocate(1);
    std::allocator_traits<allocator_rebind>::construct(alloc_rebind_, new_node,
                                                       node_type());
    new_node->data() = allocator_.allocate(1);
    std::allocator_traits<allocator_type>::construct(allocator_,
                                                     new_node->data(), val);
    return new_node;
  }

  void kill_node(node_pointer node) {
    std::allocator_traits<allocator_type>::destroy(allocator_, node->data());
    allocator_.deallocate(node->data(), 1);
    std::allocator_traits<allocator_rebind>::destroy(alloc_rebind_, node);
    alloc_rebind_.deallocate(node, 1);
  }

  node_pointer merge_sort(node_pointer head) {
    if (head == end_ || head->next() == end_) {
      return head;
    }
    node_pointer mid = split_list(head);
    node_pointer a = head;
    node_pointer b = mid->next();
    mid->next() = end_;

    a = merge_sort(a);
    b = merge_sort(b);
    return merge(a, b);
  }

  node_pointer split_list(node_pointer head) {
    node_pointer fast = head->next();
    node_pointer slow = head;

    while (fast != end_ && fast->next() != end_) {
      fast = fast->next()->next();
      slow = slow->next();
    }
    return slow;
  }

  node_pointer merge(node_pointer a, node_pointer b) {
    if (a == end_) return b;
    if (b == end_) return a;
    node_pointer c;
    if (*(a->data()) < *(b->data())) {
      c = a;
      c->next() = merge(a->next(), b);
    } else {
      c = b;
      c->next() = merge(a, b->next());
    }
    return c;
  }
};
}  // namespace s21
#endif  // SRC_S21_LIST_H_
