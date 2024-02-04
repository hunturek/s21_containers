#include "bitree.h"

int main(){
  int a[] = {13, 8, 15, 27, 25, 6, 22, 1, 11, 17};
  bitree test;
  test.set(a, 10);
  test.show();
  return 0;
}
