cmake_minimum_required(VERSION 3.10)
project(GICPLibrary)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    include
    ${EIGEN3_INCLUDE_DIR}
)

# Find Eigen3
find_package(Eigen3 REQUIRED)

# Source files
set(SOURCES
    src/GICP.cpp
)

# Create the GICP library
add_library(gicp_lib ${SOURCES})

# Test: gicp_test
add_executable(gicp_test test/gicp_test.cpp)
target_link_libraries(gicp_test gicp_lib)

# Also link KDTree if it's a separate lib (optional)
# add_library(kdtree_lib src/KDTree.cpp)
# target_link_libraries(gicp_test kdtree_lib)

# Link Eigen3 (header-only so usually just need includes)
target_include_directories(gicp_lib PRIVATE ${EIGEN3_INCLUDE_DIRS})
target_include_directories(gicp_test PRIVATE ${EIGEN3_INCLUDE_DIRS})
