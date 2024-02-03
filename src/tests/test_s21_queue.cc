#include <gtest/gtest.h>

#include "../queue/s21_queue.h"

TEST(s21_queue, empty_constructor) {
    s21::queue<int> q;
    ASSERT_EQ(0, q.size());
    ASSERT_TRUE(q.empty());
}

TEST(s21_queue, initializer_list_constructor) {
    s21::queue<int> q{1, 2, 3, 4, 5};
    ASSERT_EQ(5, q.size());
    ASSERT_FALSE(q.empty());
}

TEST(s21_queue, copy_constructor) {
    s21::queue<int> q1{1, 2, 3, 4, 5};
    s21::queue<int> q2(q1);
    ASSERT_EQ(5, q2.size());
    ASSERT_FALSE(q2.empty());
}

TEST(s21_queue, move_constructor) {
    s21::queue<int> q1{1, 2, 3, 4, 5};
    s21::queue<int> q2(std::move(q1));
    ASSERT_EQ(5, q2.size());
    ASSERT_FALSE(q2.empty());
}

TEST(s21_queue, move_assignment) {
    s21::queue<int> q1{1, 2, 3, 4, 5};
    s21::queue<int> q2;
    q2 = std::move(q1);
    ASSERT_EQ(5, q2.size());
    ASSERT_FALSE(q2.empty());
}

TEST(s21_queue, front) {
    s21::queue<int> q{1, 2, 3, 4, 5};
    ASSERT_EQ(1, q.front());
}

TEST(s21_queue, back) {
    s21::queue<int> q{1, 2, 3, 4, 5};
    ASSERT_EQ(5, q.back());
}

TEST(s21_queue, empty) {
    s21::queue<int> q;
    ASSERT_TRUE(q.empty());
    q.push(1);
    ASSERT_FALSE(q.empty());
}

TEST(s21_queue, size) {
    s21::queue<int> q;
    ASSERT_EQ(0, q.size());
    q.push(1);
    ASSERT_EQ(1, q.size());
}

TEST(s21_queue, push) {
    s21::queue<int> q;
    q.push(1);
    ASSERT_EQ(1, q.size());
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(1, q.back());
    q.push(2);
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(2, q.back());
}

TEST(s21_queue, pop) {
    s21::queue<int> q{1, 2, 3, 4, 5};
    q.pop();
    ASSERT_EQ(4, q.size());
    ASSERT_EQ(2, q.front());
    ASSERT_EQ(5, q.back());
}

TEST(s21_queue, swap) {
    s21::queue<int> q1{1, 2, 3, 4, 5};
    s21::queue<int> q2{6, 7, 8, 9, 10};
    q1.swap(q2);
    ASSERT_EQ(5, q1.size());
    ASSERT_EQ(5, q2.size());
    ASSERT_EQ(6, q1.front());
    ASSERT_EQ(5, q2.back());
}

// TODO: create a common test compiler for all containers later 
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}