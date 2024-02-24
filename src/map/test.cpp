#include "map.h"

int main() {
  s21::map<int, std::string> mp = {
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
    {13, "Masha"}
  };

  s21::map<int, std::string> mp2(mp);

  std::string value = mp.at(2);
  std::cout << "Value for key 2: " << value << std::endl;
  
  mp[02] = "Kamila";
  value = mp.at(2);
  std::cout << "Value for key 2: " << value << std::endl;
  
  value = mp.at(3);
  std::cout << "Value for key 3: " << value << std::endl;
  
  mp[93] = "Eva";
  mp[23] = "Nastya";
  
  mp.insert({3, "Sarkis"});
  value = mp.at(3);
  std::cout << "Value for key 3: " << value << std::endl;

  mp.insert(18, "Ivan");
  value = mp.at(18);
  std::cout << "Value for key 18: " << value << std::endl;

  mp.begin();
  for(size_t i = 0; i < mp.size(); i++){
    value = mp.at(mp.const_iterator());
    std::cout << "Value for iterator: " << value << std::endl;
    ++mp;
  }

  s21::map<int, std::string> tmp = {
    {11, "Adam11"},
    {22, "Adam22"},
    {33, "Adam33"},
    {44, "Adam44"},
    {55, "Adam55"},
    {66, "Adam66"},
    {77, "Adam77"},
    {88, "Adam88"}
  };
  mp.merge(tmp);

  std::cout << std::endl;

  mp.begin();
  for(size_t i = 0; i < mp.size(); i++){
    value = mp.at(mp.const_iterator());
    std::cout << "Value for iterator: " << value << std::endl;
    ++mp;
  }
  
  if(mp.empty())
    std::cout << "Empty";
  //mp(items);
  return 0;
}
