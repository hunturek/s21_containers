#include <iostream>

#define RED 1
#define BLACK 0

class bitree {
private:
  typedef struct node {
    int value = 0;
    node* parrent = nullptr;
    node* left = nullptr;
    node* right = nullptr;
    int color = 0; //0 - black, 1 - red
  }node;

  node *root;
  node *iterator;

  int balance(node*);
  int lr_check(node*);
  int rr_check(node*);
  int rc_check(node*);
  void PreOrder(node*);
  int lr(node*); //left rotate
  int rr(node*); //right rotate
  int rc(node*); //recolor

  int add_node(const int value);
  int first_root(const int value);
  
public:
  bitree(){ root = nullptr;
            iterator = nullptr; }
  ~bitree(){ }
  int set(const int value);
  int set(const int* value, size_t size);
  void show();
};

int bitree::set(const int value){
  int exit = 0;
  int null_flag = 0;
  if(root == nullptr){
    iterator = new node;
    first_root(value);
    return exit;
  } else {
    iterator = root;
  }
  while(!null_flag && exit == 0){
    if(value < iterator->value)
      if(iterator->left != nullptr) {
        iterator = iterator->left;
      } else {
        null_flag = 1;
        iterator->left = new node;
        iterator->left->parrent = iterator;
        iterator = iterator->left;
        add_node(value);
      }
    else if(value > iterator->value)
      if(iterator->right != nullptr) {
        iterator = iterator->right;
      } else {
        null_flag = 1;
        iterator->right = new node;
        iterator->right->parrent = iterator;
        iterator = iterator->right;
        add_node(value);
      }
    else if(value == iterator->value)
      exit = 1;
  }
  iterator = root;
  balance(root);
  if(exit == 1)
    std::cout << "exit = 1" << std::endl;
  return exit;
}

int bitree::set(const int* value, size_t size){
  int exit = 0;
  for(size_t i = 0; i < size && exit == 0; i++)
    exit = set(value[i]);
  return exit;
}

int bitree::first_root(const int value){
  iterator->value = value;
  iterator->parrent = nullptr;
  iterator->left = nullptr;
  iterator->right = nullptr;
  iterator->color = BLACK;
  root = iterator;
  return 0;
}

int bitree::add_node(const int value){
  iterator->value = value;
  iterator->left = nullptr;
  iterator->right = nullptr;
  iterator->color = RED;
  return 0;
}

void bitree::show(){
  iterator = root;
  char code = 0;
  while(code != 'q'){
    std::cout << iterator->value << "(" << iterator->color << ")";
    std::cout << std::endl;
    std::cin >> code;
    if(code == 'l' && iterator->left != nullptr)
      iterator = iterator->left;
    if(code == 'r' && iterator->right != nullptr)
      iterator = iterator->right;
    if(code == 'u' && iterator->parrent != nullptr)
      iterator = iterator->parrent;
  }
}

int bitree::balance(node *nd){
  if(lr_check(nd)){
    lr(nd);
    balance(root);
  }
  if(rr_check(nd)){
    rr(nd);
    balance(root);
  }
  if(rc_check(nd)){
    rc(nd);
    balance(root);
  }
  if(nd->left != nullptr)
    balance(nd->left);
  if(nd->right != nullptr)
    balance(nd->right);
  return 0;
}

int bitree::rc_check(node *nd){
  if(nd->left != nullptr && nd->right != nullptr)
    if(nd->left->color == 1 && nd->right->color == 1)
      return 1;
    else
      return 0;
}

int bitree::lr_check(node* nd){
  if(nd->left != nullptr && nd->right != nullptr)
    if(nd->left->color == 0 && nd->right->color == 1)
      return 1;
    else
      return 0;
}

int bitree::rr_check(node* nd){
  if(nd->left != nullptr)
    if(nd->left->left != nullptr)
      if(nd->left->color == 1 && nd->left->left->color == 1)
        return 1;
      else
        return 0;
}

int bitree::rc(node *nd){
  nd->left->color = 0;
  nd->right->color = 0;
  nd->color = 1;
  root->color = 0;
  return 0;
}

int bitree::lr(node *nd){
  node* parrentNode = nd;
  node* childNode = nd->right;
  childNode->parrent = parrentNode->parrent;
  parrentNode->parrent = childNode;
  parrentNode->right = childNode->left;
  parrentNode->right->parrent=parrentNode;
  childNode->left = parrentNode;
  int tmp = parrentNode->color;
  parrentNode->color = childNode->color;
  childNode->color = tmp;
  if(root == parrentNode)
    root = childNode;
  return 0;
}

int bitree::rr(node *nd){
  node* parrentNode = nd;
  node* childNode = nd->left;
  childNode->parrent = parrentNode->parrent;
  parrentNode->parrent = childNode;
  if(childNode->right != nullptr){
    parrentNode->left = childNode->right;
    parrentNode->left->parrent=parrentNode;
  }
  childNode->right = parrentNode;
  int tmp = parrentNode->color;
  parrentNode->color = childNode->color;
  childNode->color = tmp;
  if(root == parrentNode)
    root = childNode;
  return 0;
}
