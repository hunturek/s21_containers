#ifndef MULTISET_H
#define MULTISET_H
#include <iostream>
#include "../bitree/bitree.h"

namespace s21 {

template <typename Key> class multiset {
private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  bitree<Key, Key> tree;

public:
  using iterator = typename bitree<Key, Key>::tree_iterator;
  multiset() {};
  multiset(std::initializer_list<value_type> const& items){
    for (const auto& item : items) {
        tree << std::make_pair(item, item);
    }
  };
  multiset(const multiset& other) : tree(other.tree) {}
  multiset(multiset&& other) noexcept : tree(std::move(other.tree)) {}
  ~multiset() {tree.clear();}
  multiset& operator=(multiset&& other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  multiset& operator=(std::initializer_list<value_type> const& items) {
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
  iterator insert(const value_type& value) {
    iterator it = tree.begin();
    tree << std::make_pair(value, value);
    return it.set(value);
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
  void merge(multiset& other) {
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

  size_type count(const Key& key) {
    auto pos = this->equal_range(key);
    return pos.second.position - pos.first.position;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    iterator it2 = this->begin();
    iterator it1 = this->begin();
    while(it2.cget() <= key)
      ++it2;
    if(this->contains(key))
      return std::make_pair(it1.set(key), it2);
    it1 = it2;
    return std::make_pair(it1, it2);
  }

  iterator lower_bound(const Key& key) {
    iterator it = this->begin();
    while(it.cget() <= key)
      ++it;
    return it;
  } 

  iterator upper_bound(const Key& key) {
    iterator it = this->begin();
    while(it.cget() < key)
      ++it;
    return it;
  }
};

}

#endif
