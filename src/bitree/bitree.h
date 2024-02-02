#include <iostream>

#define RED 1
#define BLACK 0

class bitree {
private:
  typedef struct node {
    int* value;
    node* parrent;
    node* left;
    node* right;
    int color; //0 - black, 1 - red
    int root; //1 - root, 0 - non root
  }node;

  node *tree;
  size_t size;
  node *root;

  int balance();
  int lr(node); //left rotate
  int rr(node); //right rotate
  int rc(node); //recolor

  int add_node(int* value, node *iterator);
  int first_root(int* value);
  
public:
  bitree(){ tree = new node; 
            size = 0;         }
  ~bitree(){ delete tree; }
  int set(int* value);
  void show();
};

int bitree::set(int* value){
  int exit = 0;
  int null_flag = 0;
  node *iterator;
  if(size == 0){
    first_root(value);
    size++;
    return exit;
  } else {
    iterator = root;
  }
  while(!null_flag){
    if(*value < *iterator->value)
      if(iterator->left != nullptr) {
        iterator = iterator->left;
      } else {
        null_flag = 1;
        add_node(value, iterator);
        iterator->left = &tree[size];
        size++;
      }
    else if(*value > *iterator->value)
      if(iterator->right != nullptr) {
        iterator = iterator->right;
      } else {
        null_flag = 1;
        add_node(value, iterator);
        iterator->right = &tree[size];
        size++;
      }
    else if(*value == *iterator->value)
      exit = 1;
  }
  return 0;
}

int bitree::first_root(int* value){
  tree[size].value = value;
  tree[size].parrent = nullptr;
  tree[size].left = nullptr;
  tree[size].right = nullptr;
  tree[size].color = BLACK;
  tree[size].root = 1;
  root = &tree[size];
  return 0;
}

int bitree::add_node(int* value, node *iterator){
  tree[size].value = value;
  tree[size].parrent = iterator;
  tree[size].left = nullptr;
  tree[size].right = nullptr;
  tree[size].color = RED;
  tree[size].root = 0;
  return 0;
}
