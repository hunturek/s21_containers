#include <iostream>

#define RED 1
#define BLACK 0

template <typename T, typename T2> class bitree {
private:
  typedef struct node {
    T key;
    T2 value;
    node *parent;
    node *left;
    node *right;
    int color;
  } node;

  node *root;

  size_t tree_size;
  int add_balance(node *);
  int del_balance(node *);
  node *find(const T2);
  int lr(node *); // left rotate
  int rr(node *); // right rotate
  int rc(node *); // recolor

  int add(const T2);
  int del(const T2);

  class tree_iterator {
  private:
    typename bitree<T, T2>::node *root_node;
    int next_node();
    int back_node();
    int first_node();
    int last_node();
    size_t position;
    size_t *max_position;

  public:
    int initialize(typename bitree<T, T2>::node *tree_root, size_t *tree_size) { 
      root_node = tree_root;
      position = 0;
      max_position = tree_size;
      first_node();
      return 0;
    }

    typename bitree<T, T2>::node *current_node;

    tree_iterator &operator++() {
      next_node();
      return *this;
    }

    tree_iterator &operator--() {
      back_node();
      return *this;
    }

    tree_iterator &operator<<(int) {
      first_node();
      return *this;
    }

    tree_iterator &operator>>(int) {
      last_node();
      return *this;
    }
  };

public:

  tree_iterator iterator;
  bitree() {
    root = nullptr;
    tree_size = 0;
  }
  ~bitree() {}

  bitree &operator<<(const T2 &value) {
    if (!add(value))
      tree_size++;
    return *this;
  }

  template <size_t N> bitree &operator<<(const T2 (&values)[N]) {
    for (size_t i = 0; i < N; i++)
      this->operator<<(values[i]);
    return *this;
  }

  bitree &operator>>(const T2 &value) {
    if (!del(value))
      tree_size--;
    return *this;
  }

  template <size_t N> bitree &operator>>(const T2 (&values)[N]) {
    for (size_t i = 0; i < N; i++)
      this->operator>>(values[i]);
    return *this;
  }
  void show();
};

template <typename T, typename T2> int bitree<T, T2>::add(const T2 value) {
  node *current, *parent, *new_node;
  current = root;
  parent = nullptr;
  while (current != nullptr) {
    if (value == current->value)
      return 1;
    parent = current;
    current = value < current->value ? current->left : current->right;
  }

  new_node = new node;
  new_node->value = value;
  new_node->parent = parent;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->color = RED;

  if (parent) {
    if (value < parent->value)
      parent->left = new_node;
    else
      parent->right = new_node;
  } else {
    root = new_node;
  }

  add_balance(new_node);
  return 0;
}

template <typename T, typename T2>
typename bitree<T, T2>::node *bitree<T, T2>::find(const T2 value) {
  node *iter = root;
  while (iter != nullptr)
    if (value == iter->value)
      return iter;
    else
      iter = value < iter->value ? iter->left : iter->right;
  return 0;
}

template <typename T, typename T2> int bitree<T, T2>::del(const T2 value) {
  node *x, *y, *z = find(value);
  if (!z || z == nullptr)
    return 1;
  if (z->left == nullptr || z->right == nullptr) {
    y = z;
  } else {
    y = z->right;
    while (y->left != nullptr)
      y = y->left;
  }
  if (y->left != nullptr)
    x = y->left;
  else
    x = y->right;
  x->parent = y->parent;
  if (y->parent)
    if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;
  else
    root = x;
  if (y != z)
    z->value = y->value;
  if (y->color == BLACK)
    del_balance(x);
  free(y);
  return 0;
}

template <typename T, typename T2> void bitree<T, T2>::show() {
  node *iter = root;
  iterator.initialize(root, &tree_size);
  char code = 0;
  while (code != 'q') {
    /*std::cout << iter->value << "(" << iter->color << ")";
    std::cout << std::endl;*/
    std::cin >> code;
    if (code == 'l' && iter->left != nullptr)
      iter = iter->left;
    if (code == 'r' && iter->right != nullptr)
      iter = iter->right;
    if (code == 'u' && iter->parent != nullptr)
      iter = iter->parent;
    if (code == 'p')
      std::cout << iterator.current_node->value << std::endl;
    if (code == 'n')
      ++iterator;
  }
}

template <typename T, typename T2> int bitree<T, T2>::add_balance(node *nd) {
  while (nd != root && nd->parent->color == RED) {
    if (nd->parent == nd->parent->parent->left) {
      node *uncle = nd->parent->parent->right;
      if (uncle && uncle->color == RED) {
        rc(nd->parent->parent);
        nd = nd->parent->parent;
      } else {
        if (nd == nd->parent->right) {
          nd = nd->parent;
          lr(nd);
        }
        nd->parent->color = BLACK;
        nd->parent->parent->color = RED;
        rr(nd->parent->parent);
      }
    } else {
      node *uncle = nd->parent->parent->left;
      if (uncle && uncle->color == RED) {
        rc(nd->parent->parent);
        nd = nd->parent->parent;
      } else {
        if (nd == nd->parent->left) {
          nd = nd->parent;
          rr(nd);
        }
        nd->parent->color = BLACK;
        nd->parent->parent->color = RED;
        lr(nd->parent->parent);
      }
    }
  }
  root->color = BLACK;
  return 0;
}

template <typename T, typename T2> int bitree<T, T2>::del_balance(node *nd) {
  while (nd != root && nd->color == BLACK) {
    if (nd == nd->parent->left) {
      node *brother = nd->parent->right;
      if (brother->color == RED) {
        brother->color = BLACK;
        nd->parent->color = RED;
        lr(nd->parent);
        brother = nd->parent->right;
      }
      if (brother->left->color == BLACK && brother->right->color == BLACK) {
        brother->color = RED;
        nd = nd->parent;
      } else {
        if (brother->right->color == BLACK) {
          brother->left->color = BLACK;
          brother->color = RED;
          rr(brother);
          brother = nd->parent->right;
        }
        brother->color = nd->parent->color;
        nd->parent->color = BLACK;
        brother->right->color = BLACK;
        lr(nd->parent);
        nd = root;
      }
    } else {
      node *brother = nd->parent->left;
      if (brother->color == RED) {
        brother->color = BLACK;
        nd->parent->color = RED;
        rr(nd->parent);
        brother = nd->parent->left;
      }
      if (brother->right->color == BLACK && brother->left->color == BLACK) {
        brother->color = RED;
        nd = nd->parent;
      } else {
        if (brother->left->color == BLACK) {
          brother->right->color = BLACK;
          brother->color = RED;
          lr(brother);
          brother = nd->parent->left;
        }
        brother->color = nd->parent->color;
        nd->parent->color = BLACK;
        brother->left->color = BLACK;
        rr(nd->parent);
        nd = root;
      }
    }
  }
  nd->color = BLACK;
  return 0;
}

template <typename T, typename T2> int bitree<T, T2>::rc(node *nd) {
  nd->left->color = BLACK;
  nd->right->color = BLACK;
  nd->color = RED;
  return 0;
}

template <typename T, typename T2> int bitree<T, T2>::lr(node *nd) {
  node *pNode = nd;
  node *cNode = nd->right;
  if (!cNode)
    return 1;
  pNode->right = cNode->left;
  if (cNode->left != nullptr)
    cNode->left->parent = pNode;
  if (cNode != nullptr)
    cNode->parent = pNode->parent;
  if (pNode->parent) {
    if (pNode == pNode->parent->left)
      pNode->parent->left = cNode;
    else
      pNode->parent->right = cNode;
  } else {
    root = cNode;
  }
  cNode->left = pNode;
  if (pNode != nullptr)
    pNode->parent = cNode;
  return 0;
}

template <typename T, typename T2> int bitree<T, T2>::rr(node *nd) {
  node *pNode = nd;
  node *cNode = nd->left;
  if (!cNode)
    return 1;
  pNode->left = cNode->right;
  if (cNode->right != nullptr)
    cNode->right->parent = pNode;
  if (cNode != nullptr)
    cNode->parent = pNode->parent;
  if (pNode->parent) {
    if (pNode == pNode->parent->right)
      pNode->parent->right = cNode;
    else
      pNode->parent->left = cNode;
  } else {
    root = cNode;
  }
  cNode->right = pNode;
  if (pNode != nullptr)
    pNode->parent = cNode;
  return 0;
}

////--------------------------------------------------------------////

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::first_node() {
  current_node = root_node;
  while (current_node->left != nullptr)
    current_node = current_node->left;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::last_node() {
  current_node = root_node;
  while (current_node->right != nullptr)
    current_node = current_node->right;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::next_node() {
  if (current_node->right != nullptr) {
    current_node = current_node->right;
    while (current_node->left != nullptr)
      current_node = current_node->left;
  } else if (current_node == current_node->parent->left)
    current_node = current_node->parent;
  else if (current_node == current_node->parent->right) {
    current_node = current_node->parent;
    next_node();
  } else
    return 1;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::back_node() {
  first_node();
  for (size_t i = 0; i < position - 1; i++)
    next_node();
  return 0;
}