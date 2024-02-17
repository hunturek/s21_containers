#include "map.h"

int main() {
  std::initializer_list<int, std::string> items= {
  {54, "Adam"},
  {93, "Eva"},
  {23, "Nastya"},
  {58, "Denis"},
  {12, "Fahruh"},
  {02, "Mila"},
  {29, "Hamich"},
  {67, "Gerald"},
  {83, "Migel"},
  {71, "Gaga"},
  {39, "Yanis"},
  {91, "Basil"},
  {47, "Lasha"},
  {13, "Masha"};
  map(items) mp;
  return 0;
}
