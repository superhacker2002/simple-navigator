#ifndef SRC_S21_NODE_H_
#define SRC_S21_NODE_H_

namespace s21 {
template <typename value_type>
class Node {
private:
    Node<value_type> *prev_;
    value_type *data_;
    Node<value_type> *next_;

public:
    Node() : prev_(nullptr), data_(), next_(nullptr) {}
    Node(const value_type &val) : prev_(nullptr), data_(val), next_(nullptr) {}
    Node(Node *prev, value_type const &val, Node *next = nullptr) : prev_(prev), data_(val), next_(next) {}
    Node(Node const &other) : prev_(other.prev_), data_(other.data_), next_(other.next_) {}
    ~Node() {}

    Node &operator=(const Node &other) {
        prev_ = other.prev_;
        data_ = other.data_;
        next_ = other.next_;
        return *this;
    }

    value_type *&data() { return data_; }
    Node *&next() { return next_; }
    Node *&prev() { return prev_; }

    void insert_before_node(Node *node) {
        if (node->prev_) {
            node->prev_->next_ = this;
            prev_ = node->prev_;
        }
        node->prev_ = this;
        next_ = node;
    }

    void connect_sides_nodes() {
        if (prev_) prev_->next() = next_;
        if (next_) next_->prev() = prev_;
    }

    static void swap_nodes(Node *first, Node *second) {
        // nodes are neighbours and first is before second
        if (first->next() == second) {
            first->connect_sides_nodes();
            first->insert_before_node(second->next());
            // nodes are neighbours and second is before first
        } else if (first->prev() == second) {
            second->connect_sides_nodes();
            second->insert_before_node(first->next());
        } else {
            Node *previous = first->prev();
            Node *next = first->next();

            if (first->prev()) first->prev()->next() = second;
            if (first->next()) first->next()->prev() = second;
            first->prev() = second->prev();
            first->next() = second->next();
            if (second->prev()) second->prev()->next() = first;
            if (second->next()) second->next()->prev() = first;
            second->prev() = previous;
            second->next() = next;
        }
    }
};
}  // namespace s21

#endif  // SRC_S21_NODE_H_
