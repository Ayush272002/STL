#include <gtest/gtest.h>
#include "../containers/stack/stack.hpp"

// Test default constructor
TEST(StackTest, DefaultConstructor)
{
    stl::stack<int> st;
    EXPECT_EQ(st.size(), 0);
    EXPECT_TRUE(st.isempty());
}

// Test push function
TEST(StackTest, Push)
{
    stl::stack<int> st;
    st.push(10);
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.top(), 10);

    st.push(20);
    EXPECT_EQ(st.size(), 2);
    EXPECT_EQ(st.top(), 20);
}

// Test pop function
TEST(StackTest, Pop)
{
    stl::stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);

    st.pop();
    EXPECT_EQ(st.size(), 2);
    EXPECT_EQ(st.top(), 20);

    st.pop();
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.top(), 10);

    st.pop();
    EXPECT_TRUE(st.isempty());

    EXPECT_THROW(st.pop(), std::runtime_error);
}

// Test top function
TEST(StackTest, Top)
{
    stl::stack<int> st;
    st.push(42);
    EXPECT_EQ(st.top(), 42);

    st.push(100);
    EXPECT_EQ(st.top(), 100);

    st.pop();
    EXPECT_EQ(st.top(), 42);

    st.pop();
    EXPECT_THROW(st.top(), std::runtime_error);
}

// Test size function
TEST(StackTest, Size)
{
    stl::stack<int> st;
    EXPECT_EQ(st.size(), 0);

    st.push(5);
    st.push(15);
    EXPECT_EQ(st.size(), 2);
}

// Test isempty function
TEST(StackTest, IsEmpty)
{
    stl::stack<int> st;
    EXPECT_TRUE(st.isempty());

    st.push(1);
    EXPECT_FALSE(st.isempty());

    st.pop();
    EXPECT_TRUE(st.isempty());
}

// Test print function (Not typically tested in unit tests, but checking for no crash)
TEST(StackTest, Print)
{
    stl::stack<int> st;
    st.push(3);
    st.push(7);
    st.push(11);
    st.print(); // Ensure it doesn't crash
}
