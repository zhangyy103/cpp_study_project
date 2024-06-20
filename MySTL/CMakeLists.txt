cmake_minimum_required(VERSION 3.20)  # 指定 CMake 最低版本
project(my_stl)  # 指定项目名称

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


# 添加可执行文件
add_executable(my_stlt src/my_stl.cpp)

