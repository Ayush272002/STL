#include <gtest/gtest.h>
#include "../containers/queue/queue.hpp"

// Test default constructor
TEST(QueueTest, DefaultConstructor)
{
    stl::queue<int> q;
    EXPECT_EQ(q.size(), 0);
    EXPECT_TRUE(q.isempty());
}

// Test push function
TEST(QueueTest, Push)
{
    stl::queue<int> q;
    q.push(10);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 10);

    q.push(20);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 10);
}

// Test pop function
TEST(QueueTest, Pop)
{
    stl::queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    q.pop();
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 20);

    q.pop();
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 30);

    q.pop();
    EXPECT_TRUE(q.isempty());

    EXPECT_THROW(q.pop(), std::runtime_error);
}

// Test front function
TEST(QueueTest, Front)
{
    stl::queue<int> q;
    q.push(42);
    EXPECT_EQ(q.front(), 42);

    q.push(100);
    EXPECT_EQ(q.front(), 42);

    q.pop();
    EXPECT_EQ(q.front(), 100);

    q.pop();
    EXPECT_THROW(q.front(), std::runtime_error);
}

// Test size function
TEST(QueueTest, Size)
{
    stl::queue<int> q;
    EXPECT_EQ(q.size(), 0);

    q.push(5);
    q.push(15);
    EXPECT_EQ(q.size(), 2);
}

// Test isempty function
TEST(QueueTest, IsEmpty)
{
    stl::queue<int> q;
    EXPECT_TRUE(q.isempty());

    q.push(1);
    EXPECT_FALSE(q.isempty());

    q.pop();
    EXPECT_TRUE(q.isempty());
}

// Test print function (Not typically tested in unit tests, but checking for no crash)
TEST(QueueTest, Print)
{
    stl::queue<int> q;
    q.push(3);
    q.push(7);
    q.push(11);
    q.print(); // Ensure it doesn't crash
}
