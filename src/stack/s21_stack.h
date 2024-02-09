#ifndef S21_CONTAINERS_SRC_STACK_S21_STACK_H_
#define S21_CONTAINERS_SRC_STACK_S21_STACK_H_

#include <iostream>

namespace s21 {
    template <typename T>
    class stack {
        public:
            // type aliases
            using value_type = T;
            using size_type = std::size_t;
            using reference = T&;
            using const_reference = const T&;

            // constructors and destructor
            stack();
            stack(std::initializer_list<value_type> const& items);
            stack(const stack& s);
            stack(stack&& s);
            ~stack();

            // assignment operator
            stack& operator=(stack &&s) {
                if (this != &s) {
                    swap(s);
                }
                return *this;
            }

            // element access
            const_reference top();

            // capacity
            bool empty();
            size_type size();

            // modifiers
            void push(const_reference value);
            void pop();
            void swap(stack& other);

        private:
            struct node {
                value_type data;
                node* next;
            };

            node* head;
            size_type sz;
    };

    // constructors and destructor
    template <typename T>
    stack<T>::stack() : head(nullptr), sz(0) {}

    template <typename T>
    stack<T>::stack(std::initializer_list<value_type> const& items) : head(nullptr), sz(0) {
        for (auto const& item : items) {
            push(item);
        }
    }

    template <typename T>
    stack<T>::stack(const stack& s) : head(nullptr), sz(0) {
        for (node* current = s.head; current != nullptr; current = current->next) {
            push(current->data);
        }
    }
    
    template <typename T>
    stack<T>::stack(stack&& s) : head(nullptr), sz(0) {
        swap(s);
    }

    template <typename T>
    stack<T>::~stack() {
        while (!empty()) {
            pop();
        }
    }

    // element access
    template <typename T>
    typename stack<T>::const_reference stack<T>::top() {
        return head->data;
    }

    // capacity
    template <typename T>
    bool stack<T>::empty() {
        return sz == 0;
    }

    template <typename T>
    typename stack<T>::size_type stack<T>::size() {
        return sz;
    }

    // modifiers
    template <typename T>
    void stack<T>::push(const_reference value) {
        node* new_node = new node{value, head};
        head = new_node;
        ++sz;
    }

    template <typename T>
    void stack<T>::pop() {
        if (empty()) {
            return;
        }
        node* old_head = head;
        head = head->next;
        delete old_head;
        --sz;
    }

    template <typename T>
    void stack<T>::swap(stack& other) {
        std::swap(head, other.head);
        std::swap(sz, other.sz);
    }

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_STACK_S21_STACK_H_
