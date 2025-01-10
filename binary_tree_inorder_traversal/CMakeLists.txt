cmake_minimum_required(VERSION 3.10)
project(binary_tree_inorder_traversal)

# 设置 C++ 标准 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/include)