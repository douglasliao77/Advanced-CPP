# STL Overview

The **Standard Template Library (STL)** is a collection of powerful, generic C++ components designed for efficient data storage, access, and manipulation. It includes containers, iterators, algorithms, and function objects that enable flexible and reusable code.

## Key Components

- **Containers:**  
  Store collections of objects. Examples include `vector`, `list`, `deque`, `set`, `map`, and more.

- **Iterators:**  
  Provide a uniform way to access elements in containers, enabling generic algorithms.

- **Algorithms:**  
  Functions that operate on ranges of elements via iterators, like `sort`, `find`, `copy`, `accumulate`, etc.

- **Function Objects (Functors):**  
  Objects that can be called like functions, used to customize algorithm behavior.



## Files
1. **Hamming_Distance.cpp**
Hamming distance measures how many positions two strings differ, counting extra characters if lengths differ. The program reads a word and finds the five closest words from a word list based on this distance, then prints them.

2. **Product.cpp**  
   Defines a `Product` struct with name, price, and stock quantity, along with comparison and stream operators. Demonstrates sorting, filtering, and aggregating products using standard library algorithms.  

3. **CPU.cpp**
    Reads task intervals from a file, merges overlapping bursts, and identifies the longest active CPU periods using STL algorithm