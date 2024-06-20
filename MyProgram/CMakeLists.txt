cmake_minimum_required(VERSION 3.20)  # 指定 CMake 最低版本
project(my_program)  # 指定项目名称

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 创建静态库
add_library(gobang_lib STATIC src/gobang.cpp)
target_include_directories(gobang_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  # 包含当前目录作为公共头文件目录

add_library(push_box_lib STATIC src/push_box.cpp)
target_include_directories(push_box_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  # 包含当前目录作为公共头文件目录

# 添加可执行文件
add_executable(my_program src/my_program.cpp)

# 设置库目录
set(EASYX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/easyx4mingw_20240601/lib64)

# 链接静态库到可执行文件
target_link_libraries(my_program gobang_lib push_box_lib)

# 使用绝对路径来链接外部库
target_link_libraries(my_program ${EASYX_LIB_DIR}/libeasyx.a)
