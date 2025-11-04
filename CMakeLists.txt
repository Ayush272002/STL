cmake_minimum_required(VERSION 4.0)
project(STL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE STL_HEADERS
        include/*.hpp
        include/*.tpp
)

add_library(STL INTERFACE)
target_include_directories(STL INTERFACE include)
target_sources(STL INTERFACE ${STL_HEADERS})

enable_testing()
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.7.1
)
FetchContent_MakeAvailable(benchmark)

file(GLOB TEST_SOURCES tests/*.cpp)

# unit tests
foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE STL gtest_main)
    gtest_discover_tests(${test_name})
endforeach()

# Benchmarks
file(GLOB BENCHMARK_SOURCES benchmark/*.cpp)

foreach(bench_src ${BENCHMARK_SOURCES})
    get_filename_component(bench_name ${bench_src} NAME_WE)
    add_executable(${bench_name} ${bench_src})
    target_link_libraries(${bench_name} PRIVATE STL benchmark::benchmark benchmark::benchmark_main)
endforeach()
