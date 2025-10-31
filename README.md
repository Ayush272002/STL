# C++ STL Implementation from Scratch

This project is a custom implementation of selected components of the C++ Standard Template Library (STL). The aim is to understand the internal workings of STL, enhance coding skills, and prepare for technical interviews where such knowledge is often tested.

## Overview

This repository includes implementations of commonly used STL data structures and algorithms. Each implementation is designed to mimic the behavior of the corresponding STL component, focusing on correctness, efficiency, and reusability.

## Features

### Containers

- **Vector**: Dynamic array with contiguous memory storage, supporting random access, dynamic resizing, and efficient insertion/removal at the end.

## How to Use

### Requirements

- C++23 or later
- CMake (for build automation)
- A modern C++ compiler (e.g., g++, clang++)

### Building the Project

1. Clone the repository:
   ```bash
   git clone git@github.com:Ayush272002/STL.git
   cd STL
   ```
2. Build using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Run tests (for a specific container eg:- vector):
   ```bash
   ./test_vector
   ```