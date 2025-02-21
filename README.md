# CPDSA - Data Structures and Algorithms for Competitive Programming

## What is this?

A C++ library containing well-known data structures and algorithms not found in the C++ STL. Aims to be fast (within the confines of the STL), readable, and extensible.

This is a translation of [my personal archive](https://github.com/t-p-r/CS_archive) to standards found in modern C++ source codes.

## Prerequisites

- A C++ compiler (preferably GNU GCC 9.2+) set to compile in C++11 (`-std=c++11`) or newer standards. Some features are only supported by C++20.

## Uses

After cloning the repository, you may want to precompile the master header `cpdsa.hpp`; in which case, do note that the set of compilation options (e.g `-O2`, `-DONLINE_JUDGE` or `-pipe`) should be the same between this header and the final program.

To use, simply `#include "<path_to_CPDSA>/cpdsa.hpp"`. 

~~If you feel daring, also `#include "<path_to_CPDSA>/cpdsa_experimental.hpp"`.~~

## Reliability

Features has been self-tested on [asimon](https://github.com/t-p-r/asimon) and tested with problems found on online judges (e.g. Leetcode).

## Content

- Completed:
  - `median_heap` - a container maintaining its median.
  - `ordered_set` - dynamic segment tree to manage discrete values.
  - `buffer_scan` - a fast (~2x faster than `std::cin`, ~3x for `scanf`) way to read integral types (`int`,`size_t`, ...) from `stdin`.
  - `radix_sort` - very fast sort  (3.5 - 8.5x faster than `std::sort`) for integral types.
- Experimental:
  
- In progess:
   - `bigint` - arbitrary-precision arithmetic.
   - `graph` - graph representation.
   - `tree` - tree representation.
   - many types of string automatons (KMP, hash-based container, Aho-Corasick, ...)
