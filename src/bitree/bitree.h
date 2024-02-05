#include <iostream>

#define RED 1
#define BLACK 0


class bitree {
private:
  typedef struct node {
    int value = 0;
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
  bitree() {
    root = nullptr;
  }
  ~bitree() {}
  int set(const int value);
  int set(const int *value, size_t size);
  void show();
};

int bitree::set(const int value) {
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

int bitree::set(const int *value, size_t size) {
  int exit = 0;
  for (size_t i = 0; i < size && exit == 0; i++)
    exit = set(value[i]);
  return exit;
}

void bitree::show() {
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

int bitree::balance(node *nd) {
  node *father = nd->parrent;
  node *grandfather;
  if(father)
    grandfather = father->parrent;
    while (nd != root && nd->parrent->color == RED) {
        if (father == grandfather->left) {
            node *uncle = grandfather->right;
            if (uncle && uncle->color == RED) {
                rc(grandfather);
                nd = grandfather;
            } else {
                if (nd == father->right) {
                    nd = father;
                    lr(nd);
                }
                father->color = BLACK;
                grandfather->color = RED;
                rr(grandfather);
            }
        } else {
            node *uncle = grandfather->left;
            if (uncle && uncle->color == RED) {
                rc(grandfather);
                nd = grandfather;
            } else {
                if (nd == father->left) {
                    nd = father;
                    rr(nd);
                }
                nd->parrent->color = BLACK;
                grandfather->color = RED;
                lr(grandfather);
            }
        }
    }
    root->color = BLACK;  
    return 0;
}

int bitree::rc(node *nd) {
  nd->left->color = BLACK;
  nd->right->color = BLACK;
  nd->color = RED;
  return 0;
}

int bitree::lr(node *nd) {
  node *pNode = nd;
  node *cNode = nd->right;
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

int bitree::rr(node *nd) {
  node *pNode = nd;
  node *cNode = nd->left;
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
