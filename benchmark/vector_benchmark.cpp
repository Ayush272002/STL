#include <benchmark/benchmark.h>
#include <vector>
#include "vector/vector.hpp"

constexpr size_t N = 100000;

// ----------------------------------------
// Push Back
// ----------------------------------------
static void BM_STD_Vector_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        for (size_t i = 0; i < N; ++i)
            v.push_back(i);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STD_Vector_PushBack);

static void BM_STL_Vector_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<int> v;
        for (size_t i = 0; i < N; ++i)
            v.push_back(i);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STL_Vector_PushBack);

// ----------------------------------------
// Resize
// ----------------------------------------
static void BM_STD_Vector_Resize(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.resize(N);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STD_Vector_Resize);

static void BM_STL_Vector_Resize(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<int> v;
        v.resize(N);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STL_Vector_Resize);

// ----------------------------------------
// Insert
// ----------------------------------------
static void BM_STD_Vector_Insert(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(N);
        for (size_t i = 0; i < N; ++i)
            v.insert(v.end(), i);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STD_Vector_Insert);

static void BM_STL_Vector_Insert(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<int> v;
        v.reserve(N);
        for (size_t i = 0; i < N; ++i)
            v.insert(v.end(), i);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STL_Vector_Insert);

// ----------------------------------------
// Emplace Back
// ----------------------------------------
struct MoveOnly {
    int x;
    explicit MoveOnly(int v) : x(v) {}
    MoveOnly(MoveOnly&& other) noexcept : x(other.x) { other.x = -1; }
    MoveOnly& operator=(MoveOnly&&) = delete;
};

static void BM_STD_Vector_EmplaceBack(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<MoveOnly> v;
        for (size_t i = 0; i < N; ++i)
            v.emplace_back(i);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STD_Vector_EmplaceBack);

static void BM_STL_Vector_EmplaceBack(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<MoveOnly> v;
        for (size_t i = 0; i < N; ++i)
            v.emplace_back(i);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STL_Vector_EmplaceBack);

// ----------------------------------------
// Clear
// ----------------------------------------
static void BM_STD_Vector_Clear(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v(N, 42);
        v.clear();
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STD_Vector_Clear);

static void BM_STL_Vector_Clear(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<int> v(N, 42);
        v.clear();
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STL_Vector_Clear);

// ----------------------------------------
// Reserve
// ----------------------------------------
static void BM_STD_Vector_Reserve(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(N);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STD_Vector_Reserve);

static void BM_STL_Vector_Reserve(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<int> v;
        v.reserve(N);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_STL_Vector_Reserve);

// ----------------------------------------
// Swap
// ----------------------------------------
static void BM_STD_Vector_Swap(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> a(N, 1);
        std::vector<int> b(N, 2);
        a.swap(b);
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
}
BENCHMARK(BM_STD_Vector_Swap);

static void BM_STL_Vector_Swap(benchmark::State& state) {
    for (auto _ : state) {
        STL::vector<int> a(N, 1);
        STL::vector<int> b(N, 2);
        a.swap(b);
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
}
BENCHMARK(BM_STL_Vector_Swap);

BENCHMARK_MAIN();
