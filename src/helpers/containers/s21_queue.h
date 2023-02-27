#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::List<T>>
class Queue {
public:
    using value_type = T;
    using reference = value_type &;
    using container_type = Container;
    using const_reference = const value_type &;
    using size_type = size_t;

private:
    container_type container_;

public:
    // FUNCTIONS
    Queue(container_type const &container = container_type()) : container_(container) {}
    Queue(const Queue &other) : container_(other.container) {}
    Queue(Queue &&other) { std::move(other); }
    Queue(std::initializer_list<value_type> const &items) : container_(items) {}
    virtual ~Queue() {}
    Queue &operator=(const Queue &other) {
        container_ = other.container_;
        return *this;
    }

    // ELEMENT ACCESS
    const_reference front() const { return container_.front(); }
    const_reference back() const { return container_.back(); }

    // CAPACITY
    bool empty() const { return container_.empty(); }

    size_type size() const { return container_.size(); }

    // MODIFIERS
    void push(const_reference data) { container_.push_back(data); }

    void pop() { container_.pop_front(); }
    void swap(Queue &other) { container_.swap(other); }

    template <class... Args>
    void emplace_back(Args &&...args) {
        container_.emplace_back(std::forward<Args>(args)...);
    }
};
}  // namespace s21
