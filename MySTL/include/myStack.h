//#pragma once
////stack的实现是vector的化简版本
////Stack是继承Vector，所以底层数据结构也是数组，只不过Stack它是按照栈的逻辑结构实现的。
////比如push方法在末尾压入一个元素和pop方法就是弹出最后一个元素，search方法也是从后往前查找,这些都是因为栈的特性是后入先出。
//// 有一点要注意stack继承了Vector所以也不是严格上的栈，它能调用Vector的方法直接在中间去插入或者删除一个元素。
//#include<stack>
//#include<string>
//#include<iostream>
//using namespace std;
//
/////////////////////////////////////////////////////////////////////////////////////////栈实现四则运算表达式求值
//
//
////前缀表达式、中缀表达式、后缀表达式都是四则运算的表达方式, 用以四则运算表达式求值
////中缀表达式
////中缀表达式就是常见的运算表达式，如(3 + 4)×5 - 6
////前缀表达式
////前缀表达式又称波兰式，前缀表达式的运算符位于操作数之前
////比如 : -× + 3 4 5 6
////后缀表达式（逆波兰表达式）<这是我们使用的>
////后缀表达式又称逆波兰表达式, 与前缀表达式相似，只是运算符位于操作数之后
////比如 : 3 4 + 5 × 6 -
//
////https://www.cnblogs.com/ssyfj/p/9440307.html#%E6%A0%88%E7%9A%84%E5%BA%94%E7%94%A8%EF%BC%9A%E5%9B%9B%E5%88%99%E8%BF%90%E7%AE%97%E5%AE%9E%E7%8E%B0
//
//////判断输入的表达式是否合法
//
////括号匹配
//bool parenthesis(std::string str) {
//    int parenthesis_num = 0, bracket_num = 0, curly_num = 0;
//    for (int i = 0; i < str.length(); i++) {
//        switch (str[i]) {
//        case '(':
//            parenthesis_num += 1;
//            break;
//        case '[':
//            bracket_num += 1;
//            break;
//        case '{':
//            curly_num += 1;
//            break;
//        case ')':
//            parenthesis_num -= 1;
//            if (parenthesis_num < 0) return false;
//            break;
//        case ']':
//            bracket_num -= 1;
//            if (bracket_num < 0) return false;
//            break;
//        case '}':
//            curly_num -= 1;
//            if (curly_num < 0) return false;
//            break;
//        }
//        //parenthesis_num , bracket_num , curly_num 任意一个小于0时，即出现了括号相交)(的情况
//    }
//    if (parenthesis_num == 0 && bracket_num == 0 && curly_num == 0) return true;
//    else return false;
//}
////#
//bool operational(std::string str) {
//    std::string validCharacters = "0123456789()[]{}+-*/";
//    std::string validOperators = "+-*/";
//    //将有效的字符放入一个字符串中，并使用find()函数检查字符是否存在于该字符串中
//    //find()返回子字符串在原始字符串中第一次出现的索引位置。如果子字符串不存在，则返回 -1
//    for (auto c : str) {
//        if (validCharacters.find(c) == std::string::npos) {
//            //std::string::npos 是一个常量，表示在 std::string 类中找不到指定子串的位置。它通常用于字符串查找和替换的函数中作为返回值，表示找不到子串
//            //具体来说，std::string::npos 的值是一个 std::string::size_type 类型的常量，它被定义为一个特殊的无效位置。在大多数实现中，它的值是一个非常大的整数，例如 18446744073709551615
//            return false;
//        }
//        else if (validOperators.find(c) != std::string::npos) {
//            if (validOperators.find(c) != str.length() - 1 && validOperators.find(str[validOperators.find(c) + 1]) != std::string::npos) {
//                return false;
//            }
//            if (c == '/' && str[validOperators.find(c) + 1] == '0') {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//////在操作符与非法字符检测函数中，您可以使用一个布尔变量来标记是否是有效字符，从而避免重复的if语句。您可以使用ASCII码进行判断，将有效的字符放入一个字符串中，并使用find()函数检查字符是否存在于该字符串中
////运算符与非法字符检测
////bool operational(std::string str) {
////    for (int i = 0; i < str.length(); i++) {
////        if ((48 <= int(str[i]) && int(str[i]) <= 57) || (int(str[i]) == 40 || int(str[i]) == 41) || (int(str[i]) == 123 || int(str[i]) == 125) || (int(str[i]) == 91 || int(str[i]) == 93) || int(str[i]) == 32) {
////            //   数字 六种括号 空格
////        }
////        else if (int(str[i]) == 43 || int(str[i]) == 45 || int(str[i]) == 47 || int(str[i]) == 42) {
////            // + - * /
////            if (i < str.length() - 1) {
////                if ((i < str.length() - 1) && (int(str[i + 1]) == 43 || int(str[i + 1]) == 45 || int(str[i + 1]) == 47 || int(str[i + 1]) == 42)) {
////                    return false;
////                }
////                if (int(str[i]) == 47 && str[i + 1] == 48) {
////                    return false;
////                }
////            }
////        }
////        else return false;
////    }
////    return true;
////}
//bool isRight(std::string str) {
//    if (parenthesis(str) && operational(str))return true;
//    else return false;
//}
//
//
//std::string suffix_mode;                         //声明全局变量（真想不出方法了）
//
//void calculate() {
//    std::stack<int> calculate;
//    int i = 0;
//    while (suffix_mode[i]) {
//        if ((48 <= int(suffix_mode[i]) && int(suffix_mode[i]) <= 57)) {
//            calculate.push(suffix_mode[i]);
//        }
//        else {
//            int a, b;
//            a = calculate.top();calculate.pop();
//            b = calculate.top();calculate.pop();
//            if (suffix_mode[i] == '+') { 
//                int ans = a + b; 
//                calculate.push(ans);
//            }
//            else if (suffix_mode[i] == '-') {
//                int ans = a + b;
//                calculate.push(ans);
//            }
//            else if (suffix_mode[i] == '*') {
//                int ans = a * b;
//                calculate.push(ans);
//            }
//            else if (suffix_mode[i] == '/') {
//                int ans = a / b;
//                calculate.push(ans);
//            }
//        }
//    }
//    std::cout << calculate.top();
//    calculate.pop();
//}
//
////获取输入的表达式，存到栈中并反转，函数返回这个栈
//stack<char>* GetMidStack() {
//    //将中缀表达式存到栈中
//    std::string mode;
//    std::cin >> mode;
//    stack<char> mid_mode;
//    for (char c : mode) {
//        mid_mode.push(c);
//    }
//    //反转中缀表达式栈
//    stack<char>*alter_mid_mode = new std::stack<char>();
//    while (!mid_mode.empty()) {
//        alter_mid_mode->push(mid_mode.top());
//        mid_mode.pop();
//    }
//    return alter_mid_mode;
//}
////在C++中，std::stack是一种不允许直接复制的容器，因此不能直接返回一个stack对象
////所以使用指针或引用来返回堆栈对象
////stack<char>*的变量，将函数作为另一个函数的参数，操作拉满了，鉴定为可读性为0
//
//void GetBackStack() {//获取输入的表达式，存到栈中并反转，函数返回这个栈，将表达式转换为逆波兰表达式
//    //将中缀表达式存到栈中
//    std::string mode;
//    std::cin >> mode;
//    if (!isRight(mode)){
//        std::cout << "表达式有误";
//        return;
//    }
//    stack<char> mid_mode;
//    for (char c : mode) {
//        mid_mode.push(c);
//    }
//    //反转中缀表达式栈
//    stack<char> alter_mid_mode;
//    while (!mid_mode.empty()) {
//        alter_mid_mode.push(mid_mode.top());
//        mid_mode.pop();
//    }
//    //转换为逆波兰表达式
//    stack<char> temp;
//    stack<char> suffix_mode_stack;
//    while (!alter_mid_mode.empty()) {
//        if ((48 <= int(alter_mid_mode.top()) && int(alter_mid_mode.top()) <= 57)) {
//            suffix_mode_stack.push(alter_mid_mode.top());
//        }
//        if (alter_mid_mode.top() == '（') {
//            temp.push(alter_mid_mode.top());
//        }
//        if (alter_mid_mode.top() == ')') {
//            while (temp.top() != '(') {
//                suffix_mode_stack.push(temp.top());
//                temp.pop();
//            }
//            temp.pop();
//        }
//        if (alter_mid_mode.top() == '*' || alter_mid_mode.top() == '/') {
//            temp.push(alter_mid_mode.top());
//        }
//        if (alter_mid_mode.top() == '+' || alter_mid_mode.top() == '-') {
//            if (!temp.empty()) {
//                temp.push(alter_mid_mode.top());
//
//            }
//            else {
//                while (temp.top() != '(' || !temp.empty()) {
//                    suffix_mode_stack.push(temp.top());
//                    temp.pop();
//                }
//            }
//        }
//        alter_mid_mode.pop();
//    }
//    while (!temp.empty()) {
//        suffix_mode_stack.push(temp.top());
//        temp.pop();
//    }
//    //从左向右顺序获取中缀表达式
//    //    a.数字直接输出
//    //    b.运算符
//    //    情况一：遇到左括号直接入栈，遇到右括号将栈中左括号之后入栈的运算符全部弹栈输出，同时左括号出栈但是不输出。
//    //    情况二：遇到乘号和除号直接入栈，直到遇到优先级比它更低的运算符，依次弹栈。
//    //    情况三：遇到加号和减号，如果此时栈空，则直接入栈，否则，将栈中优先级高的运算符依次弹栈（注意：加号和减号属于同一个优先级，所以也依次弹栈）直到栈空或则遇到左括号为止，停止弹栈。（因为左括号要匹配右括号时才弹出）。
//    //    情况四：获取完后，将栈中剩余的运算符号依次弹栈输出
//    int i = 0;
//    while (!suffix_mode_stack.empty()) {
//        suffix_mode += suffix_mode_stack.top();
//        i++;suffix_mode_stack.pop();
//    }
//}
//
//
//void 栈实现四则运算表达式求值() {
//    GetBackStack();
//    calculate();
//}


#pragma once
#include <stack>
#include <string>
#include <iostream>
using namespace std;

bool parenthesis(std::string str) {
    int parenthesis_num = 0, bracket_num = 0, curly_num = 0;
    for (int i = 0; i < str.length(); i++) {
        switch (str[i]) {
        case '(':
            parenthesis_num += 1;
            break;
        case '[':
            bracket_num += 1;
            break;
        case '{':
            curly_num += 1;
            break;
        case ')':
            parenthesis_num -= 1;
            if (parenthesis_num < 0) return false;
            break;
        case ']':
            bracket_num -= 1;
            if (bracket_num < 0) return false;
            break;
        case '}':
            curly_num -= 1;
            if (curly_num < 0) return false;
            break;
        }
    }
    if (parenthesis_num == 0 && bracket_num == 0 && curly_num == 0) return true;
    else return false;
}

bool operational(std::string str) {
    std::string validCharacters = "0123456789()[]{}+-*/";
    std::string validOperators = "+-*/";
    for (auto c : str) {
        if (validCharacters.find(c) == std::string::npos) {
            return false;
        }
        else if (validOperators.find(c) != std::string::npos) {
            if (validOperators.find(c) != str.length() - 1 && validOperators.find(str[validOperators.find(c) + 1]) != std::string::npos) {
                return false;
            }
            if (c == '/' && str[validOperators.find(c) + 1] == '0') {
                return false;
            }
        }
    }
    return true;
}

bool isRight(std::string str) {
    if (parenthesis(str) && operational(str)) return true;
    else return false;
}

void calculate(std::string suffix_mode) {
    std::stack<int> calculate;
    int i = 0;
    while (suffix_mode[i]) {
        if ((48 <= int(suffix_mode[i]) && int(suffix_mode[i]) <= 57)) {
            calculate.push(suffix_mode[i]);
        }
        else {
            int a, b;
            b = calculate.top(); calculate.pop();
            a = calculate.top(); calculate.pop();
            if (suffix_mode[i] == '+') {
                int ans = a + b;
                calculate.push(ans);
            }
            else if (suffix_mode[i] == '-') {
                int ans = a - b;
                calculate.push(ans);
            }
            else if (suffix_mode[i] == '*') {
                int ans = a * b;
                calculate.push(ans);
            }
            else if (suffix_mode[i] == '/') {
                int ans = a / b;
                calculate.push(ans);
            }
        }
        i++;
    }
    std::cout << calculate.top();
    calculate.pop();
}

stack<char>* GetMidStack() {
    std::string mode;
    std::cin >> mode;
    stack<char> mid_mode;
    for (char c : mode) {
        mid_mode.push(c);
    }
    stack<char>* alter_mid_mode = new std::stack<char>();
    while (!mid_mode.empty()) {
        alter_mid_mode->push(mid_mode.top());
        mid_mode.pop();
    }
    return alter_mid_mode;
}

void GetBackStack() {
    std::string mode;
    std::cin >> mode;
    if (!isRight(mode)) {
        std::cout << "表达式有误";
        return;
    }
    stack<char> mid_mode;
    for (char c : mode) {
        mid_mode.push(c);
    }
    stack<char> alter_mid_mode;
    while (!mid_mode.empty()) {
        alter_mid_mode.push(mid_mode.top());
        mid_mode.pop();
    }
    stack<char> temp;
    stack<char> suffix_mode_stack;
    while (!alter_mid_mode.empty()) {
        if ((48 <= int(alter_mid_mode.top()) && int(alter_mid_mode.top()) <= 57)) {
            suffix_mode_stack.push(alter_mid_mode.top());
        }
        if (alter_mid_mode.top() == '(') {
            temp.push(alter_mid_mode.top());
        }
        if (alter_mid_mode.top() == ')') {
            while (temp.top() != '(') {
                suffix_mode_stack.push(temp.top());
                temp.pop();
            }
            temp.pop();
        }
        if (alter_mid_mode.top() == '*' || alter_mid_mode.top() == '/') {
            temp.push(alter_mid_mode.top());
        }
        if (alter_mid_mode.top() == '+' || alter_mid_mode.top() == '-') {
            if (!temp.empty()) {
                temp.push(alter_mid_mode.top());
            }
            else {
                while (temp.top() != '(' || !temp.empty()) {
                    suffix_mode_stack.push(temp.top());
                    temp.pop();
                }
            }
        }
        alter_mid_mode.pop();
    }
    while (!temp.empty()) {
        suffix_mode_stack.push(temp.top());
        temp.pop();
    }
    std::string suffix_mode;
    while (!suffix_mode_stack.empty()) {
        suffix_mode += suffix_mode_stack.top();
        suffix_mode_stack.pop();
    }
    calculate(suffix_mode);
}