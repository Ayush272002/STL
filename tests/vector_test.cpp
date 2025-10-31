#include "vector/vector.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <string>

TEST(Vector, DefaultConstructor) {
    const STL::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, SizeConstructor) {
    const STL::vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);

    for (int i : v)
        EXPECT_EQ(i, 0);
}

TEST(Vector, SizeValueConstructor) {
    const STL::vector<int> v(3, 42);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 3);
    for (int i : v)
        EXPECT_EQ(i, 42);
}

TEST(Vector, IteratorConstructor) {
    std::vector<int> src{1,2,3,4};
    STL::vector<int> v(src.begin(), src.end());

    EXPECT_EQ(v.size(), src.size());
    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], src[i]);
}

TEST(Vector, FromRangeConstructor_Array) {
    std::array<int, 3> arr = {5, 6, 7};
    STL::vector<int> v(std::from_range, arr);

    EXPECT_EQ(v.size(), arr.size());
    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], arr[i]);
}


TEST(Vector, FromRangeConstructor_List) {
    std::list<std::string> lst = {"a","b","c"};
    STL::vector<std::string> v(std::from_range, lst);

    EXPECT_EQ(v.size(), lst.size());

    size_t i = 0;
    for (auto& s : lst) {
        EXPECT_EQ(v[i++], s);
    }
}

TEST(Vector, CopyConstructor) {
    STL::vector<int> v1(3, 42);
    STL::vector<int> v2(v1);

    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());

    for (size_t i = 0; i < v2.size(); ++i)
        EXPECT_EQ(v2[i], v1[i]);

    EXPECT_NE(v2.data(), v1.data());
}

TEST(Vector, MoveConstructor) {
    STL::vector<int> v1(3, 99);
    int* oldData = v1.data();

    STL::vector<int> v2(std::move(v1));

    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    for (int i : v2)
        EXPECT_EQ(i, 99);

    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    EXPECT_EQ(v1.data(), nullptr);

    EXPECT_EQ(v2.data(), oldData);
}

TEST(Vector, InitializerListConstructor) {
    STL::vector<int> v = {10, 20, 30, 40};

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v.capacity(), 4);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v[3], 40);
}

TEST(Vector, CopyAssignment) {
    STL::vector<int> v1 = {1,2,3};
    STL::vector<int> v2;
    v2 = v1;  // copy assignment

    EXPECT_EQ(v2.size(), v1.size());
    for (size_t i = 0; i < v2.size(); ++i)
        EXPECT_EQ(v2[i], v1[i]);
    EXPECT_NE(v2.data(), v1.data());  // separate memory
}

TEST(Vector, MoveAssignment) {
    STL::vector<int> v1 = {4,5,6};
    int* oldData = v1.data();

    STL::vector<int> v2;
    v2 = std::move(v1);  // move assignment

    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.data(), oldData);

    EXPECT_EQ(v1.size(), 0);      // moved-from
    EXPECT_EQ(v1.data(), nullptr);
}

TEST(Vector, InitializerListAssignment) {
    STL::vector<int> v = {7, 8, 9, 10};

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 7);
    EXPECT_EQ(v[1], 8);
    EXPECT_EQ(v[2], 9);
    EXPECT_EQ(v[3], 10);
}

TEST(Vector, AssignCountValue) {
    STL::vector<int> v;
    v.assign(5, 42);

    EXPECT_EQ(v.size(), 5);
    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], 42);
}

TEST(Vector, AssignIteratorRange) {
    std::vector<int> src = {1,2,3,4};
    STL::vector<int> v;
    v.assign(src.begin(), src.end());

    EXPECT_EQ(v.size(), src.size());
    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], src[i]);
}

TEST(Vector, AssignInitializerList) {
    STL::vector<int> v;
    v.assign({7,8,9});

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 7);
    EXPECT_EQ(v[1], 8);
    EXPECT_EQ(v[2], 9);
}

TEST(Vector, AssignRangeVector) {
    std::vector<int> src = {10,20,30};
    STL::vector<int> v;
    v.assign_range(src);

    EXPECT_EQ(v.size(), src.size());
    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], src[i]);
}

TEST(Vector, AssignRangeArray) {
    std::array<int, 3> arr = {7,8,9};
    STL::vector<int> v;
    v.assign_range(arr);

    EXPECT_EQ(v.size(), arr.size());
    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], arr[i]);
}

TEST(Vector, AssignRangeView) {
    auto r = std::views::iota(1, 4); // 1,2,3
    STL::vector<int> v;
    v.assign_range(r);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(Vector, AtWithinBounds) {
    STL::vector<int> v = {10, 20, 30};
    EXPECT_EQ(v.at(0), 10);
    EXPECT_EQ(v.at(1), 20);
    EXPECT_EQ(v.at(2), 30);
}

TEST(Vector, AtOutOfBoundsThrows) {
    STL::vector<int> v = {1,2,3};
    EXPECT_THROW(v.at(3), std::out_of_range);
    EXPECT_THROW(v.at(100), std::out_of_range);
}

TEST(Vector, ConstAt) {
    const STL::vector<int> v = {7,8,9};
    EXPECT_EQ(v.at(0), 7);
    EXPECT_EQ(v.at(1), 8);
    EXPECT_EQ(v.at(2), 9);
    EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(Vector, FrontBack) {
    STL::vector<int> v = {10, 20, 30};

    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 30);

    v.front() = 1;
    v.back() = 3;

    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 3);
}

TEST(Vector, ConstFrontBack) {
    const STL::vector<int> v = {7, 8, 9};
    EXPECT_EQ(v.front(), 7);
    EXPECT_EQ(v.back(), 9);
}

TEST(Vector, EmptySizeMaxSize) {
    const STL::vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_GE(v.max_size(), v.size());
}

TEST(Vector, Reserve) {
    STL::vector<int> v = {1,2,3};
    size_t old_capacity = v.capacity();
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);

    v.reserve(50);
    EXPECT_GE(v.capacity(), 100);
}

TEST(Vector, ShrinkToFit) {
    STL::vector<int> v;
    v.reserve(100);
    v.assign({1,2,3});
    v.shrink_to_fit();

    EXPECT_EQ(v.capacity(), 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(Vector, Clear) {
    STL::vector<int> v = {1,2,3,4};
    EXPECT_EQ(v.size(), 4);

    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_GE(v.capacity(), 4);  // capacity should remain unchanged
}

TEST(Vector, SingleElement) {
    STL::vector<int> v = {1,3,4};
    v.insert(v.begin() + 1, 2);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(Vector, MultipleElements) {
    STL::vector<int> v = {1,4};
    v.insert(v.begin() + 1, 2, 3);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(Vector, IteratorRange) {
    STL::vector<int> v = {1,5};
    std::vector<int> tmp = {2,3,4};
    v.insert(v.begin() + 1, tmp.begin(), tmp.end());
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(Vector, InitializerList) {
    STL::vector<int> v = {1,4};
    v.insert(v.begin() + 1, {2,3});
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(Vector, RangeInsertVector) {
    STL::vector<int> v = {1, 5};
    std::vector<int> src = {2, 3, 4};
    v.insert(v.begin() + 1, src);

    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(Vector, RangeInsertArray) {
    STL::vector<int> v = {1, 4};
    std::array<int, 2> arr = {2, 3};
    v.insert(v.begin() + 1, arr);

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(Vector, RangeInsertView) {
    STL::vector<int> v = {0, 5};
    auto r = std::views::iota(1, 5); // 1,2,3,4
    v.insert(v.begin() + 1, r);

    EXPECT_EQ(v.size(), 6);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 3);
    EXPECT_EQ(v[4], 4);
    EXPECT_EQ(v[5], 5);
}

struct Foo {
    int a;
    int b;
    Foo(int x, int y) : a(x), b(y) {}
};

TEST(Vector, EmplaceSingle) {
    STL::vector<Foo> v;
    v.emplace(v.begin(), 1, 2);

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.front().a, 1);
    EXPECT_EQ(v.front().b, 2);

    v.emplace(v.end(), 3, 4);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back().a, 3);
    EXPECT_EQ(v.back().b, 4);
}

TEST(Vector, EmplaceMiddle) {
    STL::vector<int> v = {1, 3, 4};
    v.emplace(v.begin() + 1, 2);

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(Vector, EraseSingleElement) {
    STL::vector<int> v = {1,2,3,4};

    const auto it = v.erase(v.begin() + 1); // erase 2
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
}

TEST(Vector, EraseRange) {
    STL::vector<int> v = {10,20,30,40,50};

    const auto it = v.erase(v.begin()+1, v.begin()+4);
    // should remove 20,30,40 → left: 10,50

    EXPECT_EQ(*it, 50);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 50);
}

TEST(Vector, PushBackCopy) {
    STL::vector<int> v;
    v.push_back(10);
    v.push_back(20);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

TEST(Vector, PushBackMove) {
    STL::vector<std::string> v;
    std::string s = "hello";
    v.push_back(std::move(s));

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], "hello");
}

TEST(VectorEmplaceBack, Basic) {
    STL::vector<std::string> v;
    auto& ref = v.emplace_back("hello");

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(ref, "hello");
}

TEST(Vector, Basic) {
    STL::vector<int> v = {1,2};
    std::vector<int> src = {3,4,5};

    v.append_range(src);

    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(Vector, MoveRange) {
    STL::vector<std::string> v;
    std::vector<std::string> src = {"a","b","c"};

    v.append_range(std::move(src));

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], "a");
    EXPECT_EQ(v[1], "b");
    EXPECT_EQ(v[2], "c");
}

TEST(Vector, PopBack) {
    STL::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);

    v.pop_back();
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 10);

    v.pop_back();
    EXPECT_EQ(v.size(), 0);

    // popping empty should not crash
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

TEST(Vector, ResizeDefaultConstruct) {
    STL::vector<int> v;
    v.push_back(5);
    v.push_back(10);

    v.resize(5); // default initialize new elements

    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[1], 10);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[3], 0);
    EXPECT_EQ(v[4], 0);

    v.resize(1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 5);
}

TEST(Vector, ResizeFillValue) {
    STL::vector<int> v;
    v.resize(3, 7);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 7);
    EXPECT_EQ(v[1], 7);
    EXPECT_EQ(v[2], 7);

    // shrink down
    v.resize(1, 9);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 7); // existing value stays
}

TEST(Vector, Swap) {
    STL::vector<int> a;
    STL::vector<int> b;

    a.push_back(1);
    a.push_back(2);

    b.push_back(10);
    b.push_back(20);
    b.push_back(30);

    a.swap(b);

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
}

struct MoveOnly {
    int x;
    MoveOnly() : x(0) {}
    MoveOnly(int v) : x(v) {}
    MoveOnly(MoveOnly&& other) noexcept : x(other.x) { other.x = -1; }
    MoveOnly& operator=(MoveOnly&&) = delete;
};

TEST(Vector, ResizeMoveOnly) {
    STL::vector<MoveOnly> v;
    v.emplace_back(5);

    v.resize(3); // default-construct 2 more
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0].x, 5);
    EXPECT_EQ(v[1].x, 0);
    EXPECT_EQ(v[2].x, 0);

    v.resize(1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0].x, 5);
}

TEST(Vector, EqualityOperator) {
    const STL::vector<int> a = {1, 2, 3};
    STL::vector<int> b = {1, 2, 3};

    EXPECT_TRUE(a == b);

    b[1] = 5;
    EXPECT_FALSE(a == b);

    const STL::vector<int> c = {1, 2};
    EXPECT_FALSE(a == c);
}

TEST(Vector, ThreeWayComparison) {
    const STL::vector<int> a = {1, 2, 3};
    const STL::vector<int> b = {1, 2, 3};
    const STL::vector<int> c = {1, 2, 4};
    const STL::vector<int> d = {1, 2};

    EXPECT_TRUE((a <=> b) == 0);
    EXPECT_TRUE((a <=> c) < 0);
    EXPECT_TRUE((c <=> a) > 0);
    EXPECT_TRUE((d <=> a) < 0);
}

TEST(Vector, FreeSwap) {
    STL::vector<int> a = {1, 2, 3};
    STL::vector<int> b = {4, 5};

    swap(a, b);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);

    EXPECT_EQ(a[0], 4);
    EXPECT_EQ(b[0], 1);
}

TEST(Vector, EraseByValue) {
    STL::vector<int> v = {1, 2, 3, 2, 4};

    const size_t removed = STL::erase(v, 2);

    EXPECT_EQ(removed, 2);
    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
}

TEST(Vector, EraseIf) {
    STL::vector<int> v = {1, 2, 3, 4, 5, 6};

    const size_t removed = STL::erase_if(v, [](const int x){ return x % 2 == 0; });

    EXPECT_EQ(removed, 3);
    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 5);
}

TEST(Vector, EqualitySelf) {
    const STL::vector<int> v = {10, 20, 30};
    EXPECT_TRUE(v == v);
}
