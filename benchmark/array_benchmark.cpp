#include <benchmark/benchmark.h>
#include <array>
#include <ranges>
#include "array/array.hpp"

constexpr size_t N = 100000;

// ----------------------------------------
// Access (operator[])
// ----------------------------------------
static void BM_STD_Array_Access(benchmark::State &state) {
    std::array<int, N> a{};
    for (auto _: state) {
        for (size_t i = 0; i < N; ++i)
            benchmark::DoNotOptimize(a[i]);
    }
}

BENCHMARK(BM_STD_Array_Access);

static void BM_STL_Array_Access(benchmark::State &state) {
    STL::array<int, N> a{};
    for (auto _: state) {
        for (size_t i = 0; i < N; ++i)
            benchmark::DoNotOptimize(a[i]);
    }
}

BENCHMARK(BM_STL_Array_Access);

// ----------------------------------------
// Access (at())
// ----------------------------------------
static void BM_STD_Array_At(benchmark::State &state) {
    std::array<int, N> a{};
    for (auto _: state) {
        for (size_t i = 0; i < N; ++i)
            benchmark::DoNotOptimize(a.at(i));
    }
}

BENCHMARK(BM_STD_Array_At);

static void BM_STL_Array_At(benchmark::State &state) {
    STL::array<int, N> a{};
    for (auto _: state) {
        for (size_t i = 0; i < N; ++i)
            benchmark::DoNotOptimize(a.at(i));
    }
}

BENCHMARK(BM_STL_Array_At);

// ----------------------------------------
// Fill
// ----------------------------------------
static void BM_STD_Array_Fill(benchmark::State &state) {
    std::array<int, N> a{};
    for (auto _: state) {
        a.fill(42);
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(BM_STD_Array_Fill);

static void BM_STL_Array_Fill(benchmark::State &state) {
    STL::array<int, N> a{};
    for (auto _: state) {
        a.fill(42);
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(BM_STL_Array_Fill);

// ----------------------------------------
// Iterate
// ----------------------------------------
static void BM_STD_Array_Iterate(benchmark::State &state) {
    std::array<int, N> a{};
    for (auto _: state) {
        for (auto &v: a)
            benchmark::DoNotOptimize(v);
    }
}

BENCHMARK(BM_STD_Array_Iterate);

static void BM_STL_Array_Iterate(benchmark::State &state) {
    STL::array<int, N> a{};
    for (auto _: state) {
        for (auto &v: a)
            benchmark::DoNotOptimize(v);
    }
}

BENCHMARK(BM_STL_Array_Iterate);

// ----------------------------------------
// Reverse Iterate
// ----------------------------------------
static void BM_STD_Array_RIterate(benchmark::State &state) {
    std::array<int, N> a{};
    for (auto _: state) {
        for (int &it: std::ranges::reverse_view(a))
            benchmark::DoNotOptimize(it);
    }
}

BENCHMARK(BM_STD_Array_RIterate);

static void BM_STL_Array_RIterate(benchmark::State &state) {
    STL::array<int, N> a{};
    for (auto _: state) {
        for (int &it: std::ranges::reverse_view(a))
            benchmark::DoNotOptimize(it);
    }
}

BENCHMARK(BM_STL_Array_RIterate);

// ----------------------------------------
// Swap
// ----------------------------------------
static void BM_STD_Array_Swap(benchmark::State &state) {
    std::array<int, N> a{}, b{};
    for (auto _: state) {
        a.swap(b);
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
}

BENCHMARK(BM_STD_Array_Swap);

static void BM_STL_Array_Swap(benchmark::State &state) {
    STL::array<int, N> a{}, b{};
    for (auto _: state) {
        a.swap(b);
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
}

BENCHMARK(BM_STL_Array_Swap);

// ----------------------------------------
// Compare
// ----------------------------------------
static void BM_STD_Array_Compare(benchmark::State &state) {
    for (auto _: state) {
        std::array<int, N> a{}, b{};
        benchmark::DoNotOptimize(a == b);
    }
}

BENCHMARK(BM_STD_Array_Compare);

static void BM_STL_Array_Compare(benchmark::State &state) {
    for (auto _: state) {
        STL::array<int, N> a{}, b{};
        benchmark::DoNotOptimize(a == b);
    }
}

BENCHMARK(BM_STL_Array_Compare);

// ----------------------------------------
// to_array
// ----------------------------------------
static void BM_STD_to_array(benchmark::State &state) {
    int raw[N]{};
    for (auto _: state) {
        auto a = std::to_array(raw);
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(BM_STD_to_array);

static void BM_STL_to_array(benchmark::State &state) {
    int raw[N]{};
    for (auto _: state) {
        auto a = STL::to_array(raw);
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(BM_STL_to_array);

BENCHMARK_MAIN();
