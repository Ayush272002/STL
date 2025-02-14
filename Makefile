CC = g++
CFLAGS = -std=c++17 -Igoogletest/googletest/include
LDFLAGS = -pthread -Lgoogletest/build/lib -lgtest -lgtest_main

# Default target
all: googletest_build list_test vector_test string_test

# Build GoogleTest if not already built
googletest_build:
	cd googletest && mkdir -p build && cd build && cmake .. && make

# Compile test_vector.cpp with Google Test
vector_test: tests/test_vector.cpp containers/vector/vector.cpp googletest_build
	$(CC) $(CFLAGS) tests/test_vector.cpp containers/vector/vector.cpp -o vector_test.out $(LDFLAGS)

# Compile test_list.cpp with Google Test
list_test: tests/test_list.cpp containers/list/list.cpp googletest_build
	$(CC) $(CFLAGS) tests/test_list.cpp containers/list/list.cpp -o list_test.out $(LDFLAGS)

# Compile test_string.cpp with Google Test
string_test: tests/test_string.cpp containers/string/string.cpp googletest_build
	$(CC) $(CFLAGS) tests/test_string.cpp containers/string/string.cpp -o string_test.out $(LDFLAGS)

# Compile test_queue.cpp with Google Test
queue_test: tests/test_queue.cpp containers/queue/queue.cpp googletest_build
	$(CC) $(CFLAGS) tests/test_queue.cpp containers/queue/queue.cpp -o queue_test.out $(LDFLAGS)

# Compile test_stack.cpp with Google Test
stack_test: tests/test_stack.cpp containers/stack/stack.cpp googletest_build
	$(CC) $(CFLAGS) tests/test_stack.cpp containers/stack/stack.cpp -o stack_test.out $(LDFLAGS)

# Clean all outputs
clean:
	rm -f *.out *.o
	rm -rf googletest/build
