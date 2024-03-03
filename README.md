# CPDSA - Data Structures and Algorithms for Competitive Programming

A C++ library containing well-known data structures and algorithms not found in the C++ STL. Aims to be fast (within the confines of the STL), readable, and extensible.

This is a translation of [my personal archive](https://github.com/t-p-r/CS_archive) to standards found in modern C++ source codes.

## Prerequisites

- A C++ compiler (preferably GNU GCC 9.2.0+) set to compile in C++20 (`-std=c++20`) or newer standards.

## Uses

After cloning the repository, you may want to precompile the master header `cpdsa.hpp`; in which case, do note that all compilation flags (e.g `-O2`, `-DONLINE_JUDGE` or `-pipe`) should be the same between the header and the final program.

To use, simply `#include "<path_to_CPDSA>/cpdsa.hpp"`.

## Reliability

Headers has been self-tested on [asimon](https://github.com/t-p-r/asimon) and tested with problems found on online judges (e.g. Leetcode).

## Styles

A very simple coding style is used. Naming conventions are mostly the same with the GNU C++ library.
Line width is at most 80 characters. Indentation is done using four spaces (and not `Tab`).

The full `clang-format` style is:

`js
{ BasedOnStyle: Chromium, UseTab: Never, IndentWidth: 4, AllowShortIfStatementsOnASingleLine: true, ColumnLimit: 80 }
`

## Content

- `median_heap` - a container maintaining its median.
- `ordered_set` - dynamic segment tree to manage discrete values.
- `buffer_input` - a fast (50-75% more than `std::cin`) way to read integral types (`int`,`size_t`,...) from `stdin` (experimental).
- In progess:
   - `bigint` - arbitrary-precision arithmetic.
   - `graph` - graph representation.
   - `tree` - tree representation.
   - `weighted_graph` and `weighted_tree` - weighted variants of the structures described above.
   - `graph_algorithms` and `tree_algorithms` - do what you think it does.
