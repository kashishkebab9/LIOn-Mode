
cmake_minimum_required(VERSION 3.10)
project(KDTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Eigen3 (installed via apt as /usr/include/eigen3)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

# Add your own include directory
include_directories(include)

# Add the test executable
add_executable(kdtree_test test/kdtree_test.cpp)

# If you need to link libraries, do it here (not needed for header-only Eigen)
# target_link_libraries(kdtree_test ...)

