#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "../bitree/bitree.h"

namespace s21 {

template <typename Key, typename T> class map {
private:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using size_type = size_t;
  bitree<Key, T> tree;

public:
  using iterator = typename bitree<Key, T>::tree_iterator;
  map() {};
  map(std::initializer_list<value_type> const& items){
    for (const auto& item : items) {
        tree << item;
    }
  };
  map(const map& other) : tree(other.tree) {}
  map(map&& other) noexcept : tree(std::move(other.tree)) {}
  ~map() {tree.clear();}
  map& operator=(map&& other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  map& operator=(std::initializer_list<value_type> const& items) {
    tree.clear();
    for (const auto& item : items) {
        tree << item;
    }
    return *this;
  }

  T& at(const Key& key) {
    try {
      return tree.find_value(key);
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        static T default_value{};
        return default_value;
    }
  }
  T& operator[](const Key& key) {
    try {
        return tree.find_value(key);
    } catch (const std::out_of_range& e) {
        T tmp;
        tree << std::pair<Key, T>{key, tmp};
        return tree.find_value(key);
    }
  }

  iterator begin() {
    return tree.begin();
  }
  iterator end() {
    return tree.end();
  }

  bool empty() {
    if(tree.get_root() == nullptr)
      return true;
    else
      return false;
  }
  size_type size() {
    return tree.tree_size;
  }
  size_type max_size() {
    return 11111;
  }

  void clear() {
    tree.clear();
  }
  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = tree.begin();
    if(contains(value.first))
      return {it.set(value.first), false};
    tree << value;
    return {it.set(value.first), true};
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    iterator it = tree.begin();
    if(contains(key))
      return {it.set(key), false};
    tree << std::make_pair(key, obj);
    return {it.set(key), true};
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    iterator it = tree.begin();
    if(contains(key)){
      this->operator[](key) = obj;
      return {it.set(key), false};
    }
    tree << std::make_pair(key, obj);
    return {it.set(key), true};
  }
  void erase(iterator it) {
    tree >> it.cget();
  }
  void merge(map& other) {
    iterator it = other.begin();
    for(size_type i = 0; i < other.size(); i++){
      this->operator[](it.cget()) = other.at(it.cget());
      ++it;
    }
  }

  bool contains(const Key& key) {
  try {
    tree.find_value(key);
    return true;
    } catch (const std::out_of_range& e) {
      return false;
    }
  }
};

}

#endif
