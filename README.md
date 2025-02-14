# C++ STL Implementation from Scratch

This project is a custom implementation of selected components of the C++ Standard Template Library (STL). The aim is to understand the internal workings of STL, enhance coding skills, and prepare for technical interviews where such knowledge is often tested.

## Overview

This repository includes implementations of commonly used STL data structures and algorithms. Each implementation is designed to mimic the behavior of the corresponding STL component, focusing on correctness, efficiency, and reusability.

## Features

### Containers

- **string**: A custom string class with dynamic memory management, efficient resizing, C-string support, concatenation, and element access with bounds checking.
- **Vector**: Dynamic array with contiguous memory storage, supporting random access, dynamic resizing, and efficient insertion/removal at the end.
- **List**: A custom singly linked list implementation supporting efficient insertions and deletions at both ends and arbitrary positions, with features like dynamic memory management, size tracking, and element access.
- **Stack**: A custom stack implementation supporting dynamic resizing, efficient push/pop operations, top access, size tracking, and emptiness checking with error handling.
- **Queue**: A custom queue implementation supporting dynamic resizing, efficient push/pop operations, front access, size tracking, and emptiness checking with error handling.

## How to Use

### Requirements

- C++17 or later
- CMake (for build automation)
- A modern C++ compiler (e.g., g++, clang++)

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/Ayush272002/STL.git
   cd STL
   ```
2. Build using Make:
   ```bash
   make all
   ```
3. Run tests (for a specific container eg:- vector):
   ```bash
   make vector_test
   ./vector_test.out
   ```
