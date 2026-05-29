cmake_minimum_required(VERSION 3.10)
project(hybrid_a_star)

message(STATUS "Hybrid A star - Standalone Python Version")

# ==========================================
# STRICTLY ENFORCE C++14 GLOBALLY
# ==========================================
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Performance Optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native")

# Find Eigen (Required for matrix math)
include(cmake/FindEigen.cmake)
include_directories(${EIGEN_INCLUDE_DIR})

# Find glog (Modern CMake method for Homebrew)
find_package(glog REQUIRED)

# Include the header files directory
include_directories(include)

# ==========================================
# 1. Build the Core Algorithm
# ==========================================
add_library(
    PATH_SEARCHER_LIB SHARED
    src/rs_path.cpp
    src/hybrid_a_star.cpp
)

# Link against the modern glog target
target_link_libraries(
    PATH_SEARCHER_LIB
    glog::glog
)

# ==========================================
# 2. Python Wrapper (pybind11)
# ==========================================
find_package(pybind11 REQUIRED)

# Create the Python module
pybind11_add_module(hybrid_a_star_py src/pybind_wrapper.cpp)

# Link the module against the core library and glog
target_link_libraries(hybrid_a_star_py PRIVATE 
    PATH_SEARCHER_LIB 
    glog::glog
)