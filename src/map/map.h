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

  map &operator++() {
    ++tree.iterator;
    return *this;
  }
  map &operator--() {
    --tree.iterator;
    return *this;
  }

  void begin() {
    tree.iterator<<1;
  }
  void end() {
    tree.iterator>>1;
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
  bool insert(const value_type& value) {
    if(contains(value.first))
      return false;
    tree << value;
    tree.iterator.set(value.first);
    return true;
  }
  bool insert(const Key& key, const T& obj) {
    if(contains(key))
      return false;
    tree << std::make_pair(key, obj);
    return true;
  }
  bool insert_or_assign(const Key& key, const T& obj) {
    if(contains(key))
      this->operator[](key) = obj;
    else
      tree << std::make_pair(key, obj);
    return true;
  }
  void erase() {
    tree >> tree.iterator.cget();
  }
  void merge(map& other) {
    other.begin();
    for(size_type i = 0; i < other.size(); i++){
      this->operator[](other.const_iterator()) = other.at(other.const_iterator());
      ++other;
    }
  }

  Key& iterator(){
    return tree.iterator.get();
  }
  const Key& const_iterator(){
    return tree.iterator.cget();
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
