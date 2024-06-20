#pragma once
#include "myVector.h"
//最优队列的自实现

template<class S>
class Less {
public:
    bool operator()(const S& a, const S& b) const {
        return a < b;
    }
};
//虽然都说是二叉树,实际上是用vector实现的,但是其中siftUP和siftDown的实现都是二叉树的思想
template<class T, class Compare = Less<T>>
class myBestQueue {
private:
    myVector<T> data;
    Compare comp;

    void siftUp(int i) {
        while (i > 0 && comp(data[i], data[(i - 1) / 2])) {
            std::swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }//上浮,将最后一个元素上浮到合适的位置
    void siftDown(int i) {
        while (2 * i + 1 < data.size()) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int j = left;
            if (right < data.size() && comp(data[right], data[left]))
                j = right;
            if (!comp(data[j], data[i]))
                break;
            std::swap(data[i], data[j]);
            i = j;
        }
    }//下沉,将第一个元素下沉到合适的位置

public:
    myBestQueue() {}

    void push(const T& val) {
        data.push_back(val);
        siftUp(data.size() - 1);
    }

    void pop() {
        data[0] = data.back();
        data.pop_back();
        siftDown(0);
    }

    T top() {
        return data[0];
    }

    size_t size() {
        return data.size();
    }

    bool empty() {
        return data.empty();
    }
};