# C++学习


## 项目简介
 本文件夹用于存放我的进阶c++学习之路中的工程文件

## 工程配置
工程文件配置使用cmake来管理项目
使用git以及远程仓库来进行版本控制  
项目仓库的地址[cpp_study_project](https://github.com/ZhangYangyang0550/cpp_study_project.git)  

## 语法支持
使用了大量 **现代c++** 的新特性  
包括 **C++11、C++14、C++17、C++20**  
编译器为*mingw64*  
编译器路径 *C:/Users/32285/mingw64/bin/c++.exe*  

## 语法标准及命名规范
在工程构建时，我会尽量遵循大型c++项目构建的语法标准以及工程配置  
命名规范尽量遵循[Google 开源项目风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/index.html)  
 
### 命名示例：  
- 普通变量：hello_world  
- 资源变量：helloworld (IMAGE :(Easyx))  
- 全局变量：g_Hello_World  
- 宏定义：HELLOWORLD
- 函数：hello_world
- 结构体：HelloWorld 
- 类：HelloWorld 
- 枚举：HelloWorld 
- 命名空间：HelloWorld  
- 类的私有成员变量：_hello_world 
- 类的私有成员函数：_hello_world  
- 文件夹：HelloWorld
- 文件：hello_world
- 循环变量：i, n, m 等  
- 模板：T  

### 中文编码
在涉及到中文编码时，我会使用GB 2312的编码格式  

## 平台支持
目前本文件的运行平台均为windows  
IDE为 Visual Studio Code  
在一些项目的构建时，可能无法实现跨平台的要求  

`#include <iostream>`  
`int main(){`  
`std::cout<<"Hello ,C++"<<std::endl;`  
`return 0;`  
`}`  
![](picture.jpg)
