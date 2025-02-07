#include "stack.h"
#include <gtest.h>

TEST(stack, can_push_element) {
    TStack<int> s;
    ASSERT_NO_THROW(s.push(3));
}

TEST(stack, can_push_multiple_elements) {
    TStack<int> s;
    s.push(3);
    s.push(2);
    s.push(1);
    ASSERT_EQ(s.size(), 3);
}

TEST(stack, can_push_and_pop_element) {
    TStack<int> s;
    s.push(3);
    s.push(2);
    ASSERT_NO_THROW(s.pop());
}

TEST(stack, top) {
    TStack<int> s;
    s.push(3);
    s.push(2);
    ASSERT_EQ(s.top(), 2);
}

TEST(stack, cant_pop_from_empty) {
    TStack<int> s;
    ASSERT_ANY_THROW(s.pop());
}

TEST(stack, right_empty_for_not_empty) {
    TStack<int> s;
    s.push(3);
    s.push(2);
    ASSERT_FALSE(s.empty());
}

TEST(stack, right_empty_for_empty) {
    TStack<int> s;
    ASSERT_TRUE(s.empty());
}

TEST(stack, pop_delete_elements) {
    TStack<int> s;
    s.push(3);
    s.push(2);
    ASSERT_EQ(s.pop(), 2);
    ASSERT_EQ(s.pop(), 3);
}

TEST(stack, push_increases_size) {
    TStack<int> s;
    s.push(1);
    ASSERT_EQ(s.size(), 1);
    s.push(2);
    ASSERT_EQ(s.size(), 2);
}

TEST(stack, pop_decreases_size) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_EQ(s.size(), 1);
    s.pop();
    ASSERT_EQ(s.size(), 0);
}

TEST(stack, clear_makes_stack_empty) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    ASSERT_TRUE(s.empty());
}

TEST(stack, top_returns_last_pushed_element) {
    TStack<int> s;
    s.push(1);
    ASSERT_EQ(s.top(), 1);
    s.push(2);
    ASSERT_EQ(s.top(), 2);
}

TEST(stack, multiple_push_and_pop_operations) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    ASSERT_EQ(s.pop(), 3);
    s.push(4);
    ASSERT_EQ(s.pop(), 4);
    ASSERT_EQ(s.pop(), 2);
    ASSERT_EQ(s.pop(), 1);
}

TEST(stack, stack_empty_after_pops) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.pop();
    s.push(4);
    s.pop();
    s.pop();
    s.pop();
    ASSERT_TRUE(s.empty());
