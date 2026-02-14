cmake_minimum_required(VERSION 3.12)
project(cpdsa CXX)

# Set output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin/lib)
set(CMAKE_CXX_STANDARD 20)

# For clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compiler flags
if(MSVC)
    add_compile_options(/Zi)
else() # gcc, clang
    add_compile_options(-O3 -Wall -Wextra -pipe -g -march=native)
endif()

# Set lib folder
include_directories(include)

add_executable(test_radix_sort tests/test_radix_sort/sort_test.cpp)