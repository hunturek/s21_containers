#ifndef SET_H
#define SET_H
#include <iostream>
#include "../bitree/bitree.h"

namespace s21 {

template <typename Key> class set {
private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  bitree<Key, Key> tree;

public:
  using iterator = typename bitree<Key, Key>::tree_iterator;
  set() {};
  set(std::initializer_list<value_type> const& items){
    for (const auto& item : items) {
        tree << std::make_pair(item, item);
    }
  };
  set(const set& other) : tree(other.tree) {}
  set(set&& other) noexcept : tree(std::move(other.tree)) {}
  ~set() {tree.clear();}
  set& operator=(set&& other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  set& operator=(std::initializer_list<value_type> const& items) {
    tree.clear();
    for (const auto& item : items) {
        tree << std::make_pair(item, item);
    }
    return *this;
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
    if(contains(value))
      return {it.set(value), false};
    tree << std::make_pair(value, value);
    return {it.set(value), true};
  }
  bool erase(const value_type& value) {
    if(!this->contains(value))
      return false;
    tree >> value;
    return true;
  }
  iterator erase(iterator it) {
    iterator tmp = it;
    ++tmp;
    tree >> it.cget();
    return tmp;
  }
  void merge(set& other) {
    iterator it = other.begin();
    for(size_type i = 0; i < other.size(); i++){
      this->insert(it.cget());
      ++it;
    }
  }

  iterator find(const Key& key) {
    iterator it = this->end();
    if(!this->contains(key))
      return it;
    return it.set(key);
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
