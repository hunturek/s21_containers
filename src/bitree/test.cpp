#include "bitree.h"

int main(){
  int a = 10;
  int b = 7;
  int c = 13;
  int d = 11;
  bitree test;
  test.set(&a);
  test.set(&b);
  test.set(&c);
  test.set(&d);
  return 0;
}
