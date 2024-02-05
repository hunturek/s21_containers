#include <iostream>

#define RED 1
#define BLACK 0

template <typename T> class bitree {
private:
  typedef struct node {
    T value;
    node *parrent;
    node *left;
    node *right;
    int color;
  } node;

  node *root;

  int balance(node *);
  int lr(node *); // left rotate
  int rr(node *); // right rotate
  int rc(node *); // recolor

public:
  bitree() { root = nullptr; }
  ~bitree() {}
  int set(const T value);
  int set(const T *values, size_t size);
  void show();
};

template <typename T> int bitree<T>::set(const T value) {
  node *current, *parrent, *new_node;
  current = root;
  parrent = nullptr;
  while (current != nullptr) {
    if (value == current->value)
      return 1;
    parrent = current;
    current = value < current->value ? current->left : current->right;
  }

  new_node = new node;
  new_node->value = value;
  new_node->parrent = parrent;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->color = RED;

  if (parrent) {
    if (value < parrent->value)
      parrent->left = new_node;
    else
      parrent->right = new_node;
  } else {
    root = new_node;
  }

  balance(new_node);
  return 0;
}

template <typename T> int bitree<T>::set(const T *values, size_t size) {
  int exit = 0;
  for (size_t i = 0; i < size && exit == 0; i++)
    exit = set(values[i]);
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
    if (code == 'u' && iterator->parrent != nullptr)
      iterator = iterator->parrent;
  }
}

template <typename T> int bitree<T>::balance(node *x) {
  while (x != root && x->parrent->color == RED) {
    if (x->parrent == x->parrent->parrent->left) {
      node *y = x->parrent->parrent->right;
      if (y && y->color == RED) {
        rc(x->parrent->parrent);
        x = x->parrent->parrent;
      } else {
        if (x == x->parrent->right) {
          x = x->parrent;
          lr(x);
        }
        x->parrent->color = BLACK;
        x->parrent->parrent->color = RED;
        rr(x->parrent->parrent);
      }
    } else {
      node *y = x->parrent->parrent->left;
      if (y && y->color == RED) {
        rc(x->parrent->parrent);
        x = x->parrent->parrent;
      } else {
        if (x == x->parrent->left) {
          x = x->parrent;
          rr(x);
        }
        x->parrent->color = BLACK;
        x->parrent->parrent->color = RED;
        lr(x->parrent->parrent);
      }
    }
  }
  root->color = BLACK;
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
    cNode->left->parrent = pNode;
  if (cNode != nullptr)
    cNode->parrent = pNode->parrent;
  if (pNode->parrent) {
    if (pNode == pNode->parrent->left)
      pNode->parrent->left = cNode;
    else
      pNode->parrent->right = cNode;
  } else {
    root = cNode;
  }
  cNode->left = pNode;
  if (pNode != nullptr)
    pNode->parrent = cNode;
  return 0;
}

template <typename T> int bitree<T>::rr(node *nd) {
  node *pNode = nd;
  node *cNode = nd->left;
  if (!cNode)
    return 1;
  pNode->left = cNode->right;
  if (cNode->right != nullptr)
    cNode->right->parrent = pNode;
  if (cNode != nullptr)
    cNode->parrent = pNode->parrent;
  if (pNode->parrent) {
    if (pNode == pNode->parrent->right)
      pNode->parrent->right = cNode;
    else
      pNode->parrent->left = cNode;
  } else {
    root = cNode;
  }
  cNode->right = pNode;
  if (pNode != nullptr)
    pNode->parrent = cNode;
  return 0;
}
