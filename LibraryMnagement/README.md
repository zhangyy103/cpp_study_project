# 图书馆管理系统

## 简介
本项目设计了一个图书馆管理系统，通过程序逻辑与文本I/O操作完成整个系统的实现。  
整个工程代码命名规范，文件结构清晰，代码逻辑流畅，所有的函数与变量均封装在类中。  
充分体现出了C++这一面向对象的编程语言的特点。  
整个工程遵循 用户I/O操作复杂性 > 时间复杂度 > 代码可读性 > 空间复杂度 的要求

## 工程搭建思路
图书管理系统中，图书管理员操作的读者和图书，故首先创建`Reader`类和`Book`类。  
然而，一个图书馆管理系统不可能只操作一个读者或一本书籍，故创建`ReaderList`与`BookList`类，通过list类中的成员变量`vector<Node>list`将node类与list类联系。  
在`Reader`类中我们使用成员变量`vector<Book>borrowed_books`描述每一个读者所借的图书。  
对于读者与书籍数据的存储，我们使用了两个txt文件并通过fstream库中的文件I/O操作函数将存储数据与程序联系起来  
对于读者与书籍的增删改查操作，我们通过遍历数据存储列表来实现相应的操作

## 工程优点与特色
- 整个工程的命名规范统一，详情请查看‘命名标准’
- 对于程序中的所有函数与变量，均封装在类中，使代码易于管理与阅读
- 使用CMake配置工程，是整个工程模块化，提高了代码的可移植性。
- 防御性编程，考虑到用户可能的错误输入，并进行错误处理，防止程序卡死
- 代码注释清晰，将难以理解的语法以及逻辑标注出来(部分逻辑重复的未标出)
- 文件结构清晰，所有函数以及类的声明均在头文件中，函数的实现均在源文件中进行
- 将一些重复的代码块封装到函数中，提高代码的复用性
- 使用了大量c++11以来的语法，利用了C++的现代特性提高了代码的效率以及可读性    
    1. 在遍历操作中，使用`find_if(iterator begin, iterator end, UnaryPredicate p)`代替for循环，可以自定义回调函数，根据回调函数的返回值来判断是否找到了所需的元素
    2. 在删除操作时使用`erase(first,last)`与`remove_if(iterator begin, iterator end, UnaryPredicate p)`来删除对象，这样的操作减少了一次拷贝构造
    3. 使用`std::any`与函数多态实现了在查找操作可以根据int型的id与string型的name进行查找，减少了用户操作的复杂性
    4. 对于简单的函数使用lambda表达式，是代码更加清晰




#### 命名标准
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