#pragma once
//https://www.cnblogs.com/Lynn-Zhang/p/5429707.html 抄的
#include <cassert>//为了包含assert函数
#include<iostream>
using namespace std;
//广义表是一种非线性的数据结构，它具有极高的灵活性和广泛性。
//广义表不仅可以存储原子元素，还可以存储子表，这些子表本身也可以是广义表。
//广义表的一个经典定义是：广义表是0个或多个元素的有序集。这些元素可以是原子元素，也可以是广义表。
//python中的列表就是广义表（伟大，无需多言）支持索引等各种操作，非常灵活。
//广义表的长度就是节点的个数。广义表的深度就是广义表中的子表的层数{(1,2(3,4))深度为2，(1,(1,2,(4,5)))深度为3}

enum  Type                                           //枚举类型 用于定义一组具有离散值的常量，它可以让数据更简洁，更易读。
{
    HEAD,   //头节点
    VALUE,  //值节点
    SUB,    //子表节点
    //就是123
};

struct GeneralizedNode
{
    Type _type;       //  1.类型
    GeneralizedNode* _next;  //2.指向同层的下一个节点
    union{                                               //共用体  https://blog.csdn.net/rchris520/article/details/109232732
        char _value;    //  3.有效值
        GeneralizedNode* _subLink;     // 3.指向子表的指针
    };

    GeneralizedNode(Type type = HEAD, char value = '0') {
        _value = value;
        _type = type;
        _next = nullptr;
        if (_type == SUB) {
            _subLink = nullptr;
        }
    }
};

class Generalized{
public:
    void _Print(GeneralizedNode* head) {        //打印广义表：当节点的类型为SUB时进行递归，最后不要忘了每打印完一层要打印一个后括号。
        if (head == NULL) {
            cout << "Generalized table is NULL" << endl;
            return;
        }
        GeneralizedNode* cur = head;
        while (cur) {
            if (cur->_type == HEAD) {
                cout << '(';
            }
            else if (cur->_type == VALUE) {
                cout << cur->_value;
                if (cur->_next) {
                    cout << ',';
                }
            }
            else if (cur->_type == SUB) {
                _Print(cur->_subLink);
                if (cur->_next) {
                    cout << ',';
                }
            }
            cur = cur->_next;
        }
        cout << ')';
    }

    GeneralizedNode* _CreatList(const char*& str) { //初始化建立广义表进行循环递归。遍历字符串时遇到字符就建立值节点，遇到'('就进行递归并建立子表；遇到')'就结束当前子表的建立，并返回当前子表的头指针。
        assert(*str == '('); //如果*str不是'('直接报错 https://www.runoob.com/w3cnote/c-assert.html
        GeneralizedNode* head = new GeneralizedNode(HEAD, '0');
        GeneralizedNode* cur = head;
        str++;
        while (str != '\0')
        {
            if ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
            {
                cur->_next = new GeneralizedNode(VALUE, *str);
                cur = cur->_next;
            }
            else if (*str == '(')
            {
                cur->_next = new GeneralizedNode(SUB);
                cur = cur->_next;
                cur->_subLink = _CreatList(str);
            }
            else if (*str == ')')
            {
                return head;
            }
            str++;
        }
        return head;
    }

    size_t _Amount(GeneralizedNode* head) { //获取值节点的个数
        GeneralizedNode* begin = head;
        size_t count = 0;
        while (begin) {
            if (begin->_type == VALUE) {
                count++;
            }
            if (begin->_type == SUB) {
                count += _Amount(begin->_subLink);
            }
            begin = begin->_next;
        }
        return count;
    }

    size_t _Depth(GeneralizedNode* head) {
        if (_head == NULL) {
            return 0;
        }
        size_t dp = 0;
        GeneralizedNode* cur = head;
        size_t max = 0;
        while (cur) {
            if (cur->_type == SUB) {
                dp = _Depth(cur->_subLink);
                if (max < dp) {
                    max = dp;
                }
            }
            cur = cur->_next;
        }
        return max + 1;
    }

    GeneralizedNode* _Copy(GeneralizedNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        // 创建新节点并设置类型和有效值  
        GeneralizedNode* newNode = new GeneralizedNode(head->_type, head->_value);

        // 如果类型是SUB，则递归复制子表  
        if (newNode->_type == SUB) {
            newNode->_subLink = _Copy(head->_subLink);
        }

        // 复制同层的下一个节点  
        newNode->_next = _Copy(head->_next);

        return newNode;
    }

    void _Destory(GeneralizedNode* head) {
        if (head == NULL) {
            return;
        }
        while (head) {
            GeneralizedNode* begin = head->_next;
            if (head->_type == SUB) {
                _Destory(head->_subLink);
            }
            delete head;
            head = begin;
        }
    }
private:
    GeneralizedNode* _head; //记录广义表头指针
};
