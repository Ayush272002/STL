#include <gtest/gtest.h>
#include "../containers/vector/vector.hpp"

// Test default constructor
TEST(VectorTest, DefaultConstructor)
{
    stl::vector<int> v;

    EXPECT_EQ(v.getSize(), 0);
    EXPECT_EQ(v.getCapacity(), 0);
}

// Test push_back and indexing
TEST(VectorTest, push_backAndIndexing)
{
    stl::vector<int> v;

    v.push_back(1);
    EXPECT_EQ(v.getSize(), 1);
    EXPECT_EQ(v.getCapacity(), 1);
    EXPECT_EQ(v[0], 1);

    v.push_back(2);
    EXPECT_EQ(v.getSize(), 2);
    EXPECT_EQ(v.getCapacity(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);

    v.push_back(3);
    EXPECT_EQ(v.getSize(), 3);
    EXPECT_EQ(v.getCapacity(), 4); // Capacity doubles
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

// Test pop_back
TEST(VectorTest, pop_back)
{
    stl::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();
    EXPECT_EQ(v.getSize(), 2);
    EXPECT_EQ(v.getCapacity(), 4); // Capacity does not shrink
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

// Test resize
TEST(VectorTest, Resize)
{
    stl::vector<int> v;

    v.push_back(1);
    v.push_back(2);

    v.resize(100);
    EXPECT_EQ(v.getSize(), 2);       // Size remains unchanged
    EXPECT_EQ(v.getCapacity(), 100); // Capacity changes
}

// Test toString
TEST(VectorTest, ToString)
{
    stl::vector<int> v;

    v.push_back(1);
    v.push_back(2);

    EXPECT_EQ(v.toString(), "[1, 2]\nSize: 2 Capacity: 2\n");
}

// Test clear
TEST(VectorTest, Clear)
{
    stl::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.resize(100); // Resize to ensure capacity remains after clearing
    v.clear();

    EXPECT_EQ(v.getSize(), 0);
    EXPECT_EQ(v.getCapacity(), 100); // Capacity remains unchanged
}