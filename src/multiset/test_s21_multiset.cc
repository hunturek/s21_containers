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

TEST(s21_multiset, move_assigment) {
  s21::multiset<int> ms1 = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int> ms2;
  ms2 = std::move(ms1);
  ASSERT_EQ(14, ms2.size());
  ASSERT_FALSE(ms2.empty());
}

TEST(s21_multiset, iterator) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int>::iterator it = ms.begin();
  ASSERT_EQ(02, it.cget());
  ++it;
  ASSERT_EQ(13, it.cget());
  ++it;
  ASSERT_EQ(23, it.cget());
  ++it;
  ASSERT_EQ(23, it.cget());
  it.last_node();
  ASSERT_EQ(93, it.cget());
  ++it;
  ASSERT_EQ(02, it.cget());
  --it;
  ASSERT_EQ(93, it.cget());
  --it;
  ASSERT_EQ(83, it.cget());
  --it;
  ASSERT_EQ(83, it.cget());
}

TEST(s21_multiset, clear) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  ASSERT_EQ(14, ms.size());
  ASSERT_FALSE(ms.empty());
  ms.clear();
  ASSERT_TRUE(ms.empty());
}

TEST(s21_multiset, insert) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int>::iterator it = ms.begin();
  auto res1 = ms.insert(40);
  ASSERT_EQ(res1, it.set(40));
  auto res2 = ms.insert(41);
  ASSERT_EQ(res2, it.set(41));
  auto res3 = ms.insert(40);
  ASSERT_EQ(res3, it.set(40));
  ASSERT_TRUE(ms.contains(40));
}

TEST(s21_multiset, erase) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int>::iterator it = ms.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ASSERT_EQ(23, it.cget());
  ASSERT_TRUE(ms.contains(23));
  s21::multiset<int>::iterator it2 = ms.erase(it);
  ASSERT_EQ(29, it2.cget());
}

TEST(s21_multiset, merge) {
  s21::multiset<int> ms1 = {
    67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int> ms2 = {
    54, 93, 23, 23, 23, 02, 29, 67
  };
  ASSERT_EQ(7, ms1.size());
  ASSERT_EQ(8, ms2.size());
  ms1.merge(ms2);
  ASSERT_EQ(15, ms1.size());
}

TEST(s21_multiset, find) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int>::iterator it1 = ms.find(67);
  ASSERT_EQ(it1.cget(), 67);
  s21::multiset<int>::iterator it2 = ms.find(100);
  ASSERT_EQ(it2.cget(), 93);
}

TEST(s21_multiset, count) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  auto count = ms.count(83);
  ASSERT_EQ(5, count);
}

TEST(s21_multiset, equal_range) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  auto pos = ms.equal_range(83);
  ASSERT_EQ(pos.first.cget(), 83);
  ASSERT_EQ(pos.second.cget(), 93);
}

TEST(s21_multiset, bounds) {
  s21::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  s21::multiset<int>::iterator it1 = ms.lower_bound(23);
  s21::multiset<int>::iterator it2 = ms.upper_bound(23);
  ASSERT_EQ(29, it1.cget());
  ASSERT_EQ(23, it2.cget());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
