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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
