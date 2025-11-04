#include "array/array.hpp"
#include <gtest/gtest.h>
#include <compare>
#include <utility>

TEST(Array, AccessValidIndex) {
    STL::array<int, 3> arr = {10, 20, 30};

    EXPECT_EQ(arr.at(0), 10);
    EXPECT_EQ(arr.at(1), 20);
    EXPECT_EQ(arr.at(2), 30);

    // modify via non-const reference
    arr.at(1) = 99;
    EXPECT_EQ(arr.at(1), 99);
}

TEST(Array, AccessValidIndexConst) {
    constexpr STL::array<int, 3> arr = {5, 6, 7};

    EXPECT_EQ(arr.at(0), 5);
    EXPECT_EQ(arr.at(1), 6);
    EXPECT_EQ(arr.at(2), 7);
}

TEST(Array, ThrowsOnOutOfBounds) {
    STL::array<int, 3> arr = {1, 2, 3};

    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(Array, ThrowsOnOutOfBoundsConst) {
    constexpr STL::array<int, 3> arr = {1, 2, 3};

    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(Array, SubscriptAccessValid) {
    STL::array<int, 3> arr = {10, 20, 30};

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    // modify
    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST(Array, SubscriptAccessValidConst) {
    constexpr STL::array<int, 3> arr = {1, 2, 3};

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(Array, FrontReturnsFirstElement) {
    STL::array<int, 3> arr = {5, 6, 7};

    EXPECT_EQ(arr.front(), 5);

    // modify through reference
    arr.front() = 42;
    EXPECT_EQ(arr.front(), 42);
}

TEST(Array, FrontConst) {
    constexpr STL::array<int, 3> arr = {9, 8, 7};
    EXPECT_EQ(arr.front(), 9);
}

TEST(Array, BackReturnsLastElement) {
    STL::array<int, 3> arr = {5, 6, 7};

    EXPECT_EQ(arr.back(), 7);

    // modify through reference
    arr.back() = 100;
    EXPECT_EQ(arr.back(), 100);
}

TEST(Array, BackConst) {
    constexpr STL::array<int, 3> arr = {3, 2, 1};
    EXPECT_EQ(arr.back(), 1);
}

TEST(Array, DataReturnsPointer) {
    STL::array<int, 3> arr = {10, 20, 30};

    int* ptr = arr.data();
    EXPECT_EQ(ptr[0], 10);
    EXPECT_EQ(ptr[1], 20);
    EXPECT_EQ(ptr[2], 30);

    // Modify through pointer
    ptr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST(Array, BeginNonConst) {
    STL::array<int, 3> arr = {10, 20, 30};

    auto it = arr.begin();
    EXPECT_EQ(*it, 10);

    // iterate manually
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

TEST(Array, BeginConst) {
    constexpr STL::array<int, 3> arr = {5, 6, 7};

    auto it = arr.begin();
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(*it, 6);
    ++it;
    EXPECT_EQ(*it, 7);
}

TEST(Array, CBegin) {
    constexpr STL::array<int, 3> arr = {1, 2, 3};

    auto it = arr.cbegin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);

    // confirm it is const_iterator type
    static_assert(std::is_same_v<decltype(it), STL::array<int,3>::const_iterator>, "cbegin() must return const_iterator");
}

TEST(Array, EndNonConst) {
    STL::array<int, 3> arr = {10, 20, 30};

    auto it = arr.begin();
    for (size_t i = 0; it != arr.end(); ++it, ++i) {
        constexpr int expected_values[3] = {10, 20, 30};
        EXPECT_EQ(*it, expected_values[i]);
    }
}

TEST(Array, EndConst) {
    STL::array<int, 3> arr = {5, 6, 7};

    auto it = arr.begin();
    const auto end_it = arr.end();

    int expected = 5;
    for (; it != end_it; ++it) {
        EXPECT_EQ(*it, expected);
        ++expected;
    }

    // end() points past the last element
    EXPECT_EQ(it, arr.data() + arr.size());
}

TEST(Array, CEnd) {
    constexpr STL::array<int, 3> arr = {1, 2, 3};

    auto it = arr.cbegin();
    auto end_it = arr.cend();

    int expected = 1;
    for (; it != end_it; ++it) {
        EXPECT_EQ(*it, expected);
        ++expected;
    }

    // confirm it is const_iterator type
    static_assert(std::is_same_v<decltype(end_it), STL::array<int,3>::const_iterator>, "cend() must return const_iterator");
}

TEST(Array, RBeginNonConst) {
    STL::array<int, 3> arr = {10, 20, 30};

    auto rit = arr.rbegin();
    EXPECT_EQ(*rit++, 30);  // last element
    EXPECT_EQ(*rit++, 20);
    EXPECT_EQ(*rit++, 10);
    EXPECT_EQ(rit, arr.rend());
}

TEST(Array, RBeginConst) {
    STL::array<int, 3> arr = {1, 2, 3};

    auto rit = arr.rbegin();
    EXPECT_EQ(*rit++, 3);
    EXPECT_EQ(*rit++, 2);
    EXPECT_EQ(*rit++, 1);
    EXPECT_EQ(rit, arr.rend());
}

TEST(Array, CRBegin) {
    STL::array<int, 3> arr = {4, 5, 6};

    auto rit = arr.crbegin();
    EXPECT_EQ(*rit++, 6);
    EXPECT_EQ(*rit++, 5);
    EXPECT_EQ(*rit++, 4);
    EXPECT_EQ(rit, arr.crend());

    // check type
    static_assert(std::is_same_v<decltype(rit), STL::array<int,3>::const_reverse_iterator>,
                  "crbegin() must return const_reverse_iterator");
}

TEST(Array, REndNonConst) {
    STL::array<int, 3> arr = {10, 20, 30};

    auto rit = arr.rbegin();
    const auto rend_it = arr.rend();

    size_t i = 0;
    for (; rit != rend_it; ++rit, ++i) {
        constexpr int expected[] = {30, 20, 10};
        EXPECT_EQ(*rit, expected[i]);
    }
    EXPECT_EQ(i, arr.size());
}

TEST(Array, REndConst) {
    constexpr STL::array<int, 3> arr = {1, 2, 3};

    auto rit = arr.rbegin();
    const auto rend_it = arr.rend();

    size_t i = 0;
    for (; rit != rend_it; ++rit, ++i) {
        constexpr int expected[] = {3, 2, 1};
        EXPECT_EQ(*rit, expected[i]);
    }
    EXPECT_EQ(i, arr.size());
}

TEST(Array, CRend) {
    constexpr STL::array<int, 3> arr = {4, 5, 6};

    auto rit = arr.crbegin();
    auto rend_it = arr.crend();

    size_t i = 0;
    for (; rit != rend_it; ++rit, ++i) {
        constexpr int expected[] = {6, 5, 4};
        EXPECT_EQ(*rit, expected[i]);
    }
    EXPECT_EQ(i, arr.size());

    // check type
    static_assert(std::is_same_v<decltype(rend_it), STL::array<int,3>::const_reverse_iterator>,
                  "crend() must return const_reverse_iterator");
}

TEST(Array, Empty) {
    constexpr STL::array<int, 3> arr = {1, 2, 3};
    EXPECT_FALSE(arr.empty());

    constexpr STL::array<int, 0> empty_arr{};
    EXPECT_TRUE(empty_arr.empty());
}

TEST(Array, Size) {
    constexpr STL::array<int, 3> arr = {5, 6, 7};
    EXPECT_EQ(arr.size(), 3u);

    constexpr STL::array<float, 0> empty_arr{};
    EXPECT_EQ(empty_arr.size(), 0u);
}

TEST(Array, MaxSize) {
    constexpr STL::array<int, 5> arr{};
    EXPECT_EQ(arr.max_size(), 5u);

    constexpr STL::array<char, 0> empty_arr{};
    EXPECT_EQ(empty_arr.max_size(), 0u);
}


TEST(Array, Fill) {
    STL::array<int, 5> arr{};
    arr.fill(7);

    for (int i : arr) {
        EXPECT_EQ(i, 7);
    }

    // Test with non-POD type
    STL::array<std::string, 3> strArr;
    strArr.fill("hi");

    EXPECT_EQ(strArr[0], "hi");
    EXPECT_EQ(strArr[1], "hi");
    EXPECT_EQ(strArr[2], "hi");
}

TEST(Array, Swap) {
    STL::array<int, 3> a = {1, 2, 3};
    STL::array<int, 3> b = {4, 5, 6};

    a.swap(b);

    EXPECT_EQ(a[0], 4);
    EXPECT_EQ(a[1], 5);
    EXPECT_EQ(a[2], 6);

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);

    // Swap back to confirm swap symmetry
    a.swap(b);

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);

    EXPECT_EQ(b[0], 4);
    EXPECT_EQ(b[1], 5);
    EXPECT_EQ(b[2], 6);
}

TEST(Array, EqualOperator) {
    constexpr STL::array<int,3> a{{1,2,3}};
    constexpr STL::array<int,3> b{{1,2,3}};
    constexpr STL::array<int,3> c{{3,2,1}};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(Array, SpaceshipOperator) {
    constexpr STL::array<int,3> a{{1,2,3}};
    constexpr STL::array<int,3> b{{1,2,3}};
    constexpr STL::array<int,3> c{{1,2,4}};
    constexpr STL::array<int,3> d{{0,10,10}};

    EXPECT_TRUE((a <=> b) == std::strong_ordering::equal);
    EXPECT_TRUE((a <=> c) == std::strong_ordering::less);
    EXPECT_TRUE((c <=> a) == std::strong_ordering::greater);
    EXPECT_TRUE((d <=> a) == std::strong_ordering::less);
}

TEST(Array, GetByIndex) {
    STL::array<int,3> a{{10,20,30}};
    EXPECT_EQ(STL::get<0>(a), 10);
    EXPECT_EQ(STL::get<1>(a), 20);
    EXPECT_EQ(STL::get<2>(a), 30);

    STL::get<1>(a) = 99;
    EXPECT_EQ(a[1], 99);
}

TEST(Array, GetConst) {
    constexpr STL::array<int,3> a{{5,6,7}};
    EXPECT_EQ(STL::get<0>(a), 5);
    EXPECT_EQ(STL::get<1>(a), 6);
    EXPECT_EQ(STL::get<2>(a), 7);
}

TEST(Array, GetRvalueMove) {
    STL::array<std::string,2> a{{"hello", "world"}};
    auto s = STL::get<0>(std::move(a));
    EXPECT_EQ(s, "hello"); // value moved out
}

TEST(Array, FreeSwap) {
    STL::array<int,3> a{{1,2,3}};
    STL::array<int,3> b{{4,5,6}};

    STL::swap(a, b);

    EXPECT_EQ(a[0], 4);
    EXPECT_EQ(a[1], 5);
    EXPECT_EQ(a[2], 6);

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(Array, ToArrayLvalue) {
    int raw[3] = {7,8,9};

    auto a = STL::to_array(raw);

    EXPECT_EQ(a[0], 7);
    EXPECT_EQ(a[1], 8);
    EXPECT_EQ(a[2], 9);
}

TEST(Array, ToArrayRvalue) {
    auto a = STL::to_array<int,3>({9,8,7});

    EXPECT_EQ(a[0], 9);
    EXPECT_EQ(a[1], 8);
    EXPECT_EQ(a[2], 7);
}

TEST(Array, ToArrayRvalueMove) {
    auto a = STL::to_array<std::string,2>({"foo","bar"});
    EXPECT_EQ(a[0], "foo");
    EXPECT_EQ(a[1], "bar");
}