#ifndef LIST_ITERATOR_H_
#define LIST_ITERATOR_H_

#include "s21_node.h"

namespace s21 {
template <class T>
class ConstListIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const T;
    using pointer = const value_type *;
    using reference = const value_type &;
    using node_pointer = Node<T> *;

private:
    node_pointer const_iterator_;

public:
    ConstListIterator() : const_iterator_(nullptr) {}
    ConstListIterator(node_pointer it) : const_iterator_(it) {}
    ConstListIterator(const ConstListIterator &it) : const_iterator_(it.const_iterator_) {}
    ConstListIterator(ConstListIterator &&it) : const_iterator_(it.const_iterator_) {}
    ~ConstListIterator() { const_iterator_ = nullptr; }

    ConstListIterator &operator++() {
        const_iterator_ = const_iterator_->next();
        return *this;
    }

    ConstListIterator &operator++(int) {
        auto it = *this;
        it.const_iterator_ = it.const_iterator_->next();
        return *this;
    }
    ConstListIterator &operator--() {
        const_iterator_ = const_iterator_->prev();
        return *this;
    }

    bool operator==(const ConstListIterator &it) {
        return const_iterator_->data() == it.const_iterator_->data();
    }
    bool operator!=(const ConstListIterator &it) { return const_iterator_ != it.const_iterator_; }
    void operator=(const ConstListIterator &it) { const_iterator_ = it.const_iterator_; }
    void operator=(ConstListIterator &&it) { const_iterator_ = it.const_iterator_; }
    reference operator*() { return *(const_iterator_->data()); }

    ConstListIterator operator+(int value) {
        ConstListIterator tmp(*this);
        return (tmp += value);
    }

    ConstListIterator operator-(int value) {
        ConstListIterator tmp(*this);
        return (tmp -= value);
    }

    ConstListIterator &operator+=(int value) {
        for (int i = 0; i < value; i++) {
            const_iterator_ = const_iterator_->next();
        }
        return *this;
    }

    ConstListIterator &operator-=(int value) {
        for (int i = 0; i < value; i++) {
            const_iterator_ = const_iterator_->prev();
        }
        return *this;
    }

    pointer operator->() { return const_iterator_->data(); }

    node_pointer base() {
        node_pointer pointer = const_iterator_;
        return pointer;
    }
};
template <class T>
class ListIterator {
public:
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;
    using node_pointer = Node<value_type> *;
    using const_iterator = typename s21::ConstListIterator<value_type>;

private:
    node_pointer iterator_;

public:
    ListIterator() : iterator_(nullptr) {}
    ListIterator(node_pointer it) : iterator_(it) {}
    ListIterator(const ListIterator &it) : iterator_(it.iterator_) {}
    ListIterator(ListIterator &&it) : iterator_(it.iterator_) {}
    ListIterator(const_iterator &other) { iterator_ = other.const_iterator_; }
    ~ListIterator() { iterator_ = nullptr; }

    ListIterator &operator++() {
        iterator_ = iterator_->next();
        return *this;
    }

    ListIterator &operator++(int) {
        auto it = *this;
        it.iterator_ = it.iterator_->next();
        return *this;
    }
    ListIterator &operator--() {
        iterator_ = iterator_->prev();
        return *this;
    }

    bool operator==(const ListIterator &it) { return iterator_->data() == it.iterator_->data(); }
    bool operator!=(const ListIterator &it) { return iterator_ != it.iterator_; }
    void operator=(const ListIterator &it) { iterator_ = it.iterator_; }
    void operator=(ListIterator &&it) { iterator_ = it.iterator_; }
    reference operator*() { return *(iterator_->data()); }

    ListIterator operator+(int value) {
        ListIterator tmp(*this);
        return (tmp += value);
    }

    ListIterator operator-(int value) {
        ListIterator tmp(*this);
        return (tmp -= value);
    }

    ListIterator &operator+=(int value) {
        for (int i = 0; i < value; i++) {
            iterator_ = iterator_->next();
        }
        return *this;
    }

    ListIterator &operator-=(int value) {
        for (int i = 0; i < value; i++) {
            iterator_ = iterator_->prev();
        }
        return *this;
    }

    pointer operator->() { return iterator_->data(); }

    node_pointer base() {
        node_pointer pointer = iterator_;
        return pointer;
    }
};
}  // namespace s21

#endif  // LIST_ITERATOR_H_