#include "bitree2.h"

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
  s21::bitree<int, char> test;
  test << a;
    //s21::bitree<int, char>::tree_iterator it = test.begin();
    s21::bitree<int, char>::tree_iterator it = test.begin();
    for(it; it != test.end(); ++it) {
        std::cout << it.get() << std::endl;
    }
  std::cout << it.get() << std::endl;
  test.clear();
  return 0;
}
