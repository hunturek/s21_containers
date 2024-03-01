#include <gtest/gtest.h>

#include "multiset.h"

TEST(s21_multiset, empty_constructor) {
  s21::multiset<int> s;
  ASSERT_EQ(0, s.size());
  ASSERT_TRUE(s.empty());
}

TEST(s21_multiset, initializer_constructor) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  ASSERT_EQ(14, ms.size());
  ASSERT_FALSE(ms.empty());
}

TEST(s21_multiset, copy_contructor) {
  s21::multiset<int> ms1 = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int> ms2(ms1);
  ASSERT_EQ(14, ms2.size());
  ASSERT_FALSE(ms2.empty());
}

TEST(s21_multiset, move_constructor) {
  s21::multiset<int> ms1 = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int> ms2(std::move(ms1));
  ASSERT_EQ(14, ms2.size());
  ASSERT_FALSE(ms2.empty());
}

/*TEST(s21_multiset, move_assigment) {
  s21::multiset<int> s1 = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  s21::multiset<int> s2;
  s2 = std::move(s1);
  ASSERT_EQ(14, s2.size());
  ASSERT_FALSE(s2.empty());
}

TEST(s21_multiset, iterator) {
  s21::multiset<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  s21::multiset<int>::iterator it = s.begin();
  ASSERT_EQ(02, it.cget());
  ++it;
  ASSERT_EQ(12, it.cget());
  ++it;
  ASSERT_EQ(13, it.cget());
  it.last_node();
  ASSERT_EQ(93, it.cget());
  ++it;
  ASSERT_EQ(02, it.cget());
  --it;
  ASSERT_EQ(93, it.cget());
}

TEST(s21_multiset, clear) {
  s21::multiset<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  ASSERT_EQ(14, s.size());
  ASSERT_FALSE(s.empty());
  s.clear();
  ASSERT_TRUE(s.empty());
}

TEST(s21_multiset, insert) {
  s21::multiset<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  s21::multiset<int>::iterator it = s.begin();
  auto res1 = s.insert(40);
  ASSERT_EQ(res1, std::make_pair(it.multiset(40), true));
  auto res2 = s.insert(41);
  ASSERT_EQ(res2, std::make_pair(it.multiset(41), true));
  auto res3 = s.insert(40);
  ASSERT_EQ(res3, std::make_pair(it.multiset(40), false));
  ASSERT_TRUE(s.contains(40));
}

TEST(s21_multiset, erase) {
  s21::multiset<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  s21::multiset<int>::iterator it = s.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ASSERT_EQ(39, it.cget());
  ASSERT_TRUE(s.contains(39));
  s.erase(it);
  ASSERT_FALSE(s.contains(39));
}

TEST(s21_multiset, merge) {
  s21::multiset<int> s1 = {
    54, 93, 23, 58, 12, 02, 29, 67
  };
  s21::multiset<int> s2 = {
    67, 83, 71, 39, 91, 47, 13
  };
  ASSERT_EQ(8, s1.size());
  ASSERT_EQ(7, s2.size());
  s1.merge(s2);
  ASSERT_EQ(14, s1.size());
}

TEST(s21_multiset, find) {
  s21::multiset<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  s21::multiset<int>::iterator it1 = s.find(67);
  ASSERT_EQ(it1.cget(), 67);
  s21::multiset<int>::iterator it2 = s.find(100);
  ASSERT_EQ(it2.cget(), 93);
}
*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
