#include <gtest/gtest.h>
#include "../containers/list/list.hpp"

TEST(ListTest, DefaultConstructor)
{
    stl::list<int> nums;
    EXPECT_EQ(nums.getSize(), 0);
    EXPECT_TRUE(nums.is_empty());
}

TEST(LinkedListTest, PushBackAndGetSize)
{
    stl::list<int> nums;
    nums.push_back(10);
    EXPECT_EQ(nums.getSize(), 1);
    EXPECT_FALSE(nums.is_empty());
    nums.push_back(20);
    nums.push_back(30);
    EXPECT_EQ(nums.getSize(), 3);
}

TEST(LinkedListTest, PushFront)
{
    stl::list<int> nums;
    nums.push_front(5);
    EXPECT_EQ(nums.getSize(), 1);
    EXPECT_EQ(nums.front(), 5);
}

TEST(LinkedListTest, FrontAndBack)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);
    EXPECT_EQ(nums.front(), 10);
    EXPECT_EQ(nums.back(), 30);
}

TEST(LinkedListTest, PopFront)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);
    EXPECT_EQ(nums.pop_front(), 10);
    EXPECT_EQ(nums.getSize(), 2);
    EXPECT_EQ(nums.front(), 20);
}

TEST(LinkedListTest, PopBack)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);
    EXPECT_EQ(nums.pop_back(), 30);
    EXPECT_EQ(nums.getSize(), 2);
    EXPECT_EQ(nums.back(), 20);
}

TEST(LinkedListTest, Insert)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.insert(1, 15); // Insert 15 at index 1
    EXPECT_EQ(nums.getSize(), 3);
    EXPECT_EQ(nums[0], 10);
    EXPECT_EQ(nums[1], 15);
    EXPECT_EQ(nums[2], 20);
}

TEST(LinkedListTest, Erase)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(15);
    nums.push_back(20);
    nums.erase(1); // Remove element at index 1
    EXPECT_EQ(nums.getSize(), 2);
    EXPECT_EQ(nums[0], 10);
    EXPECT_EQ(nums[1], 20);
}

TEST(LinkedListTest, OperatorSquareBrackets)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums[1] = 25; // Modify element at index 1
    EXPECT_EQ(nums[1], 25);
}

TEST(LinkedListTest, Clear)
{
    stl::list<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.clear();
    EXPECT_EQ(nums.getSize(), 0);
    EXPECT_TRUE(nums.is_empty());
}

TEST(LinkedListTest, ErrorHandling)
{
    stl::list<int> nums;

    // pop_front on empty list
    EXPECT_THROW(nums.pop_front(), std::runtime_error);

    // pop_back on empty list
    EXPECT_THROW(nums.pop_back(), std::runtime_error);

    // erase out of bounds
    EXPECT_THROW(nums.erase(0), std::runtime_error);

    // insert out of bounds
    EXPECT_THROW(nums.insert(1, 50), std::runtime_error);

    // operator[] out of bounds
    EXPECT_THROW(nums[0], std::runtime_error);
}

TEST(LinkedListTest, ReuseAfterClear)
{
    stl::list<int> nums;
    nums.push_back(100);
    nums.push_front(50);
    EXPECT_EQ(nums.getSize(), 2);
    EXPECT_EQ(nums.front(), 50);
    EXPECT_EQ(nums.back(), 100);
}