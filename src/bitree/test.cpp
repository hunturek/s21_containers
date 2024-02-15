#include "bitree.h"

int main() {
  std::initializer_list<std::pair<int, char>> a{
  {59,'a'},
  {5,'f'},
  {27,'e'},
  {34,'c'},
  {45,'q'},
  {56,'g'},
  {73,'s'},
  {91,'t'},
  {10,'x'},
  {19,'z'},
  {31,'b'},
  {50,'u'},
  {78,'j'},
  {85,'l'},
  {14,'v'},
  {40,'o'},
  {65,'n'},
  {82,'d'},
  {24,'d'},
  {69,'d'},
  {62,'d'}};
  bitree<int, char> test;
  test << a;
  test.show();
  ++test.iterator;
  test.show();
  test.clear();
  return 0;
}
