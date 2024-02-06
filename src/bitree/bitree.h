#include <iostream>

#define RED 1
#define BLACK 0

template <typename T> class bitree {
private:
  typedef struct node {
    T value;
    node *parent;
    node *left;
    node *right;
    int color;
  } node;

  node *root;

  int add_balance(node *);
  int del_balance(node *);
  node *find(const T);
  int lr(node *); // left rotate
  int rr(node *); // right rotate
  int rc(node *); // recolor

public:
  bitree() { root = nullptr; }
  ~bitree() {}
  int add(const T);
  int add(const T *, size_t);
  int del(const T);
  int del(const T *, size_t);
  void show();
};

template <typename T> int bitree<T>::add(const T value) {
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

template <typename T> int bitree<T>::add(const T *values, size_t size) {
  int exit = 0;
  for (size_t i = 0; i < size && exit == 0; i++)
    exit = add(values[i]);
  return exit;
}

template <typename T> typename bitree<T>::node* bitree<T>::find(const T value) {
  node *iterator = root;
  while (iterator != nullptr)
    if (value == iterator->value)
      return iterator;
    else
      iterator = value < iterator->value ? iterator->left : iterator->right;
  return 0;
}

template <typename T> int bitree<T>::del(const T value) {
	node *x, *y, *z = find(value);
    if (!z || z == nullptr) return 1;
    if (z->left == nullptr || z->right == nullptr) {
        y = z;
    } else {
        y = z->right;
        while (y->left != nullptr) y = y->left;
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
    if (y != z) z->value = y->value;
    if (y->color == BLACK)
        del_balance(x);
    free(y);
	return 0;
}

template <typename T> int bitree<T>::del(const T *values, size_t size) {
  int exit = 0;
  for (size_t i = 0; i < size && exit == 0; i++)
    exit = del(values[i]);
  return exit;
}

template <typename T> void bitree<T>::show() {
  node *iterator = root;
  char code = 0;
  while (code != 'q') {
    std::cout << iterator->value << "(" << iterator->color << ")";
    std::cout << std::endl;
    std::cin >> code;
    if (code == 'l' && iterator->left != nullptr)
      iterator = iterator->left;
    if (code == 'r' && iterator->right != nullptr)
      iterator = iterator->right;
    if (code == 'u' && iterator->parent != nullptr)
      iterator = iterator->parent;
  }
}

template <typename T> int bitree<T>::add_balance(node *nd) {
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

template <typename T> int bitree<T>::del_balance(node *nd) {
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

template <typename T> int bitree<T>::rc(node *nd) {
  nd->left->color = BLACK;
  nd->right->color = BLACK;
  nd->color = RED;
  return 0;
}

template <typename T> int bitree<T>::lr(node *nd) {
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

template <typename T> int bitree<T>::rr(node *nd) {
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
