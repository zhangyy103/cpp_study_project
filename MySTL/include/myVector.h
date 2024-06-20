#pragma once
template<typename T>
class myVector {

public:
	typedef T value_type;
	typedef T* iterator;   //value  和 iterator 都是T型的别名
private:
	value_type* _data; //用于申请一段连续空间的指针
	size_t _size; //用于存放该vector对象中存放元素的个数
	size_t _capacity; //用于存放vector对象所申请的空间大小

public:
	myVector() {	//构造函数
		_data = NULL;
		_size = 0;
		_capacity = 0;
	}

	~myVector() {	//析构函数
		delete[] _data;
		_data = NULL;
		_size = 0;
		_capacity = 0;
	}

	myVector(const myVector& vec) {	//拷贝构造函数
		_size = vec._size;
		_capacity = vec._capacity;
		_data = new value_type[_capacity];
		for (int i = 0;i < _size;++i) {
			_data[i] = vec._data[i];
		}
	}

	myVector operator=(const myVector& vec) {	//赋值运算符重载函数
		if (this == &vec) return *this;
		value_type* temp = new value_type[vec._capacity];
		for (int i = 0;i < vec._size;++i) {
			temp[i] = vec._data[i];
		}
		delete[] _data;
		_data = temp;
		_size = vec._size;
		_capacity = vec._capacity;
		return *this;
	}

	value_type& operator[](size_t index) {	//[]运算符重载函数（用于取出vector实例化对象的第index个元素）
		return _data[index];
	}

	bool operator==(const myVector& vec)const {		//== 运算符重载函数（用于判断两个vector对象是否相等）
		if (_size != vec._size) return false;
		for (int i = 0; i < _size; ++i) {
			if (_data[i] != vec._data[i])
				return false;
		}
		return true;
	}

	void push_back(value_type val) {	//向vector示例化对象增添元素（尾插法）
		if (_capacity == 0) {
			_capacity = 1;
			_data = new value_type[1];
		}
		else if (_size + 1 > _capacity) {
			_capacity *= 2;
			value_type* temp = new value_type[_capacity];
			for (int i = 0; i < _size; ++i) {
				temp[i] = _data[i];
			}
			delete[] _data;
			_data = temp;
		}
		_data[_size] = val;
		++_size;
	}

	void pop_back() {		//删除vector实例化对象最后一个元素
		--_size;
		value_type* temp = new value_type[_capacity];
		for (int i = 0; i < _size; ++i) {
			temp[i] = _data[i];
		}
		delete[] _data;
		_data = temp;
	}

	void insert(iterator it, value_type val) {	//向vector实例化对象的it位置插入一个元素
		int index = it - _data;//it是一个指向数组中某个元素的迭代器，而_data是数组的首地址。因此，it-_data计算的是从数组的开始到it所指向的元素之间的元素数量。将计算得到的差值存储在整数变量index中。这样，index就表示了it所指向的元素在数组中的位置或索引。
		if (_capacity == 0) {
			_capacity = 1;
			_data = new value_type[_capacity];
			_data[0] = val;
		}
		else if (_size + 1 > _capacity) {
			_capacity *= 2;
			value_type* temp = new value_type[_capacity];
			for (int i = 0; i < index; ++i) {
				temp[i] = _data[i];
			}
			temp[index] = val;
			for (int i = index; i < _size; i++) {
				temp[i + 1] = _data[i];
			}//这里将原来index位置及其以后的元素向后移，所以，原有的数据没有被替换，而是向后移动了一位
			delete[] _data;
			_data = temp;
		}
		else {
			for (int i = _size - 1; i >= index; --i) {
				_data[i + 1] = _data[i];
			}//将原index及其以后的元素后移一位，此时index位置为空
			_data[index] = val;//为index位置赋值
		}//所以，原有的数据没有被替换，而是向后移动了一位
		++_size;
	}

	void erase(iterator it) {		//删除vector实例化对象it位置的元素
		size_t index = it - _data;
		value_type* temp = new value_type[_capacity];
		for (int i = 0; i < index; ++i) {
			temp[i] = _data[i];
		}
		for (int i = index + 1; i < _size; ++i) {
			temp[i - 1] = _data[i];
		}
		delete[] _data;
		_data = temp;
		--_size;
	}

	void resize(int num, value_type val) {		//指定容器的长度为num。若容器变长，则使用val填充位置，若变短，则删除超出的元素
		value_type* temp = new value_type[num];
		if (_size == num)return;
		if (_size > num) {
			for (int i = 0; i < num; ++i) {
				temp[i] = _data[i];
			}
			delete _data;
			_data = temp;
		}
		if (_size < num) {
			for (int i = 0; i < _size; ++i) {
				temp[i] = _data[i];
			}
			for (int i = _size;i < num;i++) {
				temp[i] = val;
			}
			delete _data;
			_data = temp;
		}
	}

	value_type front()const {		//取出vector对象中的第一个元素
		return _data[0];
	}

	value_type back()const {		//取出vector对象中的最后一个元素
		return _data[_size - 1];
	}

	iterator begin() { return _data; }		//获取vector实例化对象的元素首地址

	iterator end() { return _data + _size; }		//获取vector实例化对象的最后一个元素的下一个地址

	size_t size()const {		//获取vector实例化对象的元素个数
		return _size;
	}

	size_t capacity()const {		//获取vector实例化对象所占空间大小
		return _capacity;
	}

	bool empty() {		//判断vector实例化对象是否为空
		return _size == 0;
	}
};

//reference——https://blog.csdn.net/weixin_50941083/article/details/122354948?spm=1001.2014.3001.5506

//Why size_t matters?
//使用size_t可能会提高代码的可移植性、有效性或者可读性，或许同时提高这三者。
//
//参数中带有size_t的函数通常会含有局部变量用来对数组的大小或者索引进行计算，在这种情况下，size_t是个不错的选择。
//适当地使用size_t还会使你的代码变得如同自带文档。当你看到一个对象声明为size_t类型，你马上就知道它代表字节大小或数组索引，而不是错误代码或者是一个普通的算术值。
//https://jeremybai.github.io/blog/2014/09/10/size-t