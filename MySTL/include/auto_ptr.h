#pragma once
//RAII 机制是 C++编程中一项重要的资源管理策略
//它通过将对象的生命周期与资源的生命周期绑定，简化了资源管理代码，提高了程序的安全性。

//智能指针就是封装在类中的成员指针参数，在析构函数中使用delete方法将指针释放从而实现指针在可行域内被释放，避免内存泄漏

//std::unique_ptr:
//
//特点：独占性拥有指针所指向的对象。资源独立于其他智能指针或原始指针。
//用途：适用于独占资源的情况，例如动态分配的内存、文件句柄等。
//适用时机：当需要在多个代码块之间传递拥有权或确保资源的唯一所有者时，使用std::unique_ptr。
//
//std::shared_ptr:
//
//特点：使用引用计数来管理资源，可以被多个智能指针共享。资源在最后一个引用被释放后才会被销毁。
//用途：适用于需要多个智能指针共享同一个资源的情况，例如多个对象需要访问同一个动态分配的内存块。
//适用时机：当需要在多个代码块之间共享资源或进行动态资源管理时，使用std::shared_ptr。
//
//std::weak_ptr:
//
//特点：是std::shared_ptr的一种观察者，指向一个由std::shared_ptr管理的对象，但不增加引用计数。cc
//用途：适用于解决循环引用问题，以避免资源的泄漏，并在需要时允许访问由std::shared_ptr管理的对象。
//适用时机：当存在循环引用风险或需要进行临时观察而不增加引用计数时，使用std::weak_ptr。
//
//std::auto_ptr（已弃用）：
//
//特点：在早期版本的C++中出现，类似于std::unique_ptr，但它的所有权可以转移，具有不够智能和安全的特点。
//用途：已被std::unique_ptr取代，在现代C++中不再推荐使用。
//
//需要注意的是，选择适当的智能指针类型取决于资源所有权的特征和需求。通常情况下，优先使用std::unique_ptr
//只有在需要共享资源或解决循环引用等情况下，才考虑使用std::shared_ptr和std::weak_ptr。同时，避免直接使用裸指针来管理资源，以减少内存泄漏和悬挂指针的风险。

#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass Constructor" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass Destructor" << std::endl;
    }

    void doSomething() {
        std::cout << "Doing something..." << std::endl;
    }
};

int ato_ptr() {
    // 使用 std::unique_ptr 来管理资源
    std::unique_ptr<MyClass> uniquePtr(new MyClass());

    uniquePtr->doSomething();

    // 使用 std::shared_ptr 共享资源所有权
    std::shared_ptr<MyClass> sharedPtr1(new MyClass());
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;
    sharedPtr1->doSomething();
    sharedPtr2->doSomething();

    // sharedPtr1 和 sharedPtr2 在此处超过作用域，资源仍然不会被释放
    // 直到最后一个引用离开作用域
    return 0;
}
