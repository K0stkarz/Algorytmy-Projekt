# Skip List Implementation in C++
A modern C++ implementation of a Skip List data structure using smart pointers and templated classes.

## Table of Contents
- [Skip List Implementation in C++](#skip-list-implementation-in-c)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Features](#features)
  - [Implementation Details](#implementation-details)
    - [Random Level Generation](#random-level-generation)
  - [Class Structure](#class-structure)
    - [SkipNode](#skipnode)
    - [SkipList](#skiplist)
  - [Usage](#usage)
  - [Time Complexity](#time-complexity)
  - [References](#references)

## Overview
A Skip List is a probabilistic data structure that allows for faster search within an ordered sequence of elements. It is built in layers where the bottom layer is an ordinary ordered linked list, and each higher layer acts as an "express lane" for the lists below, where an element in layer i appears in layer i+1 with some fixed probability p (usually 0.5).

## Features
- Template-based implementation supporting any comparable data type
- Modern C++ implementation using smart pointers (`std::shared_ptr`)
- Thread-safe random number generation using `std::mt19937`
- Configurable maximum level and promotion probability
- Support for standard container operations (insert, remove, search)
- Move semantics support
- Copy semantics support

## Implementation Details
The implementation consists of two main components:
1. `SkipNode`: A structure template representing a node in the Skip List
2. `SkipList`: The main class template implementing the Skip List functionality

### Random Level Generation
The implementation uses modern C++ random number facilities:
- `std::random_device` for generating seed values
- `std::mt19937` (Mersenne Twister) as the random number generator
- `std::uniform_real_distribution` for generating random probabilities

## Class Structure

### SkipNode
```cpp
template <typename T>
struct SkipNode {
    T value;
    std::vector<std::shared_ptr<SkipNode<T>>> forward;
    
    SkipNode(const T& val, int level);
    SkipNode();
};
```

### SkipList
```cpp
template <typename T>
class SkipList {
public:
    SkipList();
    SkipList(int maxLvl, float p);
    SkipList(const SkipList& other);
    SkipList(SkipList&& other) noexcept;
    
    void insert(const T& value);
    void remove(const T& value);
    std::shared_ptr<SkipNode<T>> search(const T& value) const;
    void clear();
    bool empty() const;
    void display() const;
};
```

## Usage
```cpp
// Create a skip list with default parameters (maxLevel = 5, probability = 0.5)
SkipList<int> skipList;

// Insert elements
skipList.insert(3);
skipList.insert(6);
skipList.insert(7);
skipList.insert(9);
skipList.insert(12);

// Search for an element
auto node = skipList.search(6);
if (node) {
    std::cout << "Found: " << node->value << std::endl;
}

// Remove an element
skipList.remove(7);

// Display the skip list structure
skipList.display();
```

## Time Complexity
- Search: O(log n) average case
- Insert: O(log n) average case
- Delete: O(log n) average case
- Space Complexity: O(n log n) average case

Where n is the number of elements in the Skip List.

## References
- [Skip List - Wikipedia](https://en.wikipedia.org/wiki/Skip_list)
- [std::shared_ptr - cppreference](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [std::mt19937 - GeeksForGeeks](https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/)
- [std::random_device - cppreference](https://en.cppreference.com/w/cpp/numeric/random/random_device)
- [std::uniform_real_distribution - cppreference](https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution)