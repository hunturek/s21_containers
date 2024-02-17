#include <iostream>
#include "../bitree/bitree.h"

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
  map(std::initializer_list<value_type> const &items) {
    tree << items;
  };
  /*map(const map &m) {};
  map(const map &&m) {};
  ~map() {};
  map &operator=(map &&m) {
    map(m);
    return *this;
  }*/

  T& at(const Key& key) {
    try {
      return tree.find_value(key);
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
  };
  map &operator[](const Key& key) {
    try {
      T tmp = tree.find_value(key);
      if(!tmp)
        return tmp;
      else
        throw(tmp);
    } catch (T tmp) {
      tree << std::pair<Key, T>{key,tmp};
    }
  };

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
    if(tree.root == nullptr)
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
      this[key] = obj;
    else
      tree << std::make_pair(key, obj);
    return true;
  }
  void erase() {
    tree >> tree.iterator.get();
  }

  bool contains(const Key& key) {
    return !tree.find_value(key);
  }
};
