#include <gtest/gtest.h>

#include "map.h"

TEST(s21_map, empty_constructor) {
  s21::map<int, std::string> m;
  ASSERT_EQ(0, m.size());
  ASSERT_TRUE(m.empty());
}

TEST(s21_map, initializer_constructor) {
  s21::map<int, std::string> m = {
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
  ASSERT_EQ(14, m.size());
  ASSERT_FALSE(m.empty());
}

TEST(s21_map, copy_contructor) {
  s21::map<int, std::string> m1 = {
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
  s21::map<int, std::string> m2(m1);
  ASSERT_EQ(14, m2.size());
  ASSERT_FALSE(m2.empty());
}

TEST(s21_map, move_constructor) {
  s21::map<int, std::string> m1 = {
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
  s21::map<int, std::string> m2(std::move(m1));
  ASSERT_EQ(14, m2.size());
  ASSERT_FALSE(m2.empty());
}

TEST(s21_map, move_assigment) {
  s21::map<int, std::string> m1 = {
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
  s21::map<int, std::string> m2;
  m2 = std::move(m1);
  ASSERT_EQ(14, m2.size());
  ASSERT_FALSE(m2.empty());
}

TEST(s21_map, at) {
  s21::map<int, std::string> m = {
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
  ASSERT_EQ("Hamich", m.at(29));
  ASSERT_EQ("Fahruh", m.at(12));
  ASSERT_EQ("Basil", m.at(91));
}

TEST(s21_map, operator) {
  s21::map<int, std::string> m = {
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
  ASSERT_EQ("Hamich", m.at(29));
  m[29] = "Givi";
  ASSERT_EQ("Givi", m.at(29));
  m[29] = "Sveta";
  ASSERT_EQ("Sveta", m.at(29));
}

TEST(s21_map, iterator) {
  s21::map<int, std::string> m = {
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
  m.begin();
  ASSERT_EQ(02, m.iterator());
  ++m;
  ASSERT_EQ(12, m.iterator());
  ++m;
  ASSERT_EQ(13, m.iterator());
  m.end();
  ASSERT_EQ(93, m.iterator());
  ++m;
  ASSERT_EQ(02, m.iterator());
  --m;
  --m;
  ASSERT_EQ(93, m.iterator());
}

TEST(s21_map, clear) {
  s21::map<int, std::string> m = {
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
  ASSERT_EQ(14, m.size());
  ASSERT_FALSE(m.empty());
  m.clear();
  ASSERT_TRUE(m.empty());
}

TEST(s21_map, insert) {
  s21::map<int, std::string> m = {
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
  m.insert(std::make_pair((int)40, (std::string)"Valentina"));
  ASSERT_EQ("Valentina", m.at(40));
  m.insert((int)41, (std::string)"Stas");
  ASSERT_EQ("Stas", m.at(41));
  m.insert_or_assign((int)40, (std::string)"Valya");
  ASSERT_EQ("Valya", m.at(40));
}

TEST(s21_map, erase) {
  s21::map<int, std::string> m = {
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
  m.begin();
  ++m;
  ++m;
  ++m;
  ++m;
  ++m;
  ASSERT_EQ(39, m.iterator());
  ASSERT_TRUE(m.contains(39));
  m.erase();
  ASSERT_FALSE(m.contains(39));
}

TEST(s21_map, merge) {
  s21::map<int, std::string> m1 = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
  };
  s21::map<int, std::string> m2 = {
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  ASSERT_EQ(8, m1.size());
  ASSERT_EQ(7, m2.size());
  m1.merge(m2);
  ASSERT_EQ(14, m1.size());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
