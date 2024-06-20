cmake_minimum_required(VERSION 3.20)  # 指定 CMake 最低版本
project(lib_management)  # 指定项目名称

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 创建静态库
add_library(book_lib STATIC src/book.cpp)
target_include_directories(book_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  # 包含当前目录作为公共头文件目录

add_library(reader_lib STATIC src/reader.cpp)
target_include_directories(reader_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  # 包含当前目录作为公共头文件目录

# 添加可执行文件
add_executable(lib_management src/lib_management.cpp)



# 链接静态库到可执行文件
target_link_libraries(lib_management book_lib reader_lib)

