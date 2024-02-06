#include "bitree.h"

int main() {
  int a[] = {59,5,27,34,45,56,73,91,10,19,31,50,78,85,14,40,65,82,24,69,62};
  std::string c[] = {"Denis",   "Nastya", "Basil", "Larisa", "Olya",
                     "Natasha", "Liza",   "Vova",  "Sergey", "Sasha"};
  std::string b[] = {"13", "8", "15", "27", "25", "6", "22", "1", "11", "17"};
  bitree<std::string, int> test;
  test.add(a, 10);
  test.show();
  return 0;
}
