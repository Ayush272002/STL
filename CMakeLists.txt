cmake_minimum_required(VERSION 4.0)
project(STL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB STL_HEADERS include/vector/*.hpp include/vector/*.tpp)

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
file(GLOB TEST_SOURCES tests/*.cpp)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(test_${test_name} ${test_src})
    target_link_libraries(test_${test_name} PRIVATE STL gtest_main)
    gtest_discover_tests(test_${test_name})
endforeach()
