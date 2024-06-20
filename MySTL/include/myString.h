#include <iostream>
size_t _strlen(const char* str) {
	if (str == nullptr)return 0;
	size_t len = 0;
	while (*str != '\0') {//避免了str为nullptr引发的问题
		len++;
		str++;
	}
	return len;
}//求字符串长度

char* _strcpy(char* dest, const char* src) {
	size_t dest_length = 0;
	while (dest != nullptr && dest[dest_length] != '\0')dest_length++;
	size_t src_length = 0;
	while (src != nullptr && src[src_length] != '\0')src_length++;//求dest和scr的长度（不含有'\0')
	size_t length = dest_length > src_length ? dest_length : src_length;//取最大值
	delete[] dest;
	dest = new char[length + 1];
	for (size_t i = 0;i < length;i++)dest[i] = src[i];//将scr复制到dest
	dest[length] = '\0';
	return dest;
} //dest变成scr

char* _strcat(char* dest, const char* src) {
	if (dest == nullptr && src == nullptr)return nullptr;
	size_t dest_length = 0;
	while (dest != nullptr && dest[dest_length] != '\0')dest_length++;
	size_t src_length = 0;
	while (src != nullptr && src[src_length] != '\0')src_length++;//求dest和scr的长度（不含有'\0')
	char* res = new char[dest_length + src_length + 1];//为res分配合适的空间
	for (size_t i = 0;i < dest_length;i++)res[i] = dest[i];//将dest复制到res
	for (size_t j = dest_length;j < dest_length + src_length;j++)res[j] = src[j - dest_length];//将scr赋值给res
	res[dest_length + src_length] = '\0';//在结尾加上'\0'
	delete[] dest;
	return res;

}//res = dest + scr

int _strcmp(const char* str1, const char* str2)
{
	int ret = 0;
	while (!(ret = *(unsigned char*)str1 - *(unsigned char*)str2) && *str1)
	{
		str1++;
		str2++;
	}
	if (ret < 0)
		return -1;
	else if (ret > 0)
		return 1;
	return 0;
}//比较两个字符串的大小

class myString {
private:
	char* _data;		//字符串
	size_t _length;		//长度  占用的空间时_length+1

public:
	myString(const char* str = "") {		//构造函数
		_length = _strlen(str);
		_data = new char[_length + 1];
		_data = _strcpy(_data, str);
	}
	myString(const wchar_t* str) {		//构造函数
		//const wchar_t* 转化为  const char*
		_length = wcslen(str);
		_data = new char[_length + 1];
		char* w_data = new char[_length + 1];
		for (size_t i = 0; i < _length; i++) {
			w_data[i] = str[i];
		}
		w_data[_length] = '\0';
		_data = _strcpy(_data, w_data);
		delete[] w_data;
	}
	myString(int n, char c) {//使用n个字符c初始化 构造函数
		_length = n;
		_data = new char[_length + 1];
		for (size_t i = 0; i < n; i++) {
			_data[i] = c;
		}
		_data[n] = '\0';
	}
	myString(const myString& str) {			//拷贝构造
		this->_length = str._length;
		_data = new char[_length + 1];
		_data = _strcpy(_data, str._data);
	}

	~myString() {
		if (_data != nullptr)delete[] _data;
		_data = nullptr;
		_length = 0;
	}

	myString& operator=(const myString& str) {
		delete[] _data;
		_length = str._length;
		_data = new char[_length + 1];
		_data = _strcpy(_data, str._data);
		return *this;
	}

	myString& operator=(const char* str) {
		delete[] _data;
		_length = _strlen(str);
		_data = new char[_length + 1];
		_data = _strcpy(_data, str);
		return *this;
	}

	myString operator+(const char* str) {
		myString temp;
		temp._length = _length + _strlen(str);
		temp._data = new char[temp._length + 1];
		temp._data = _strcat(_data, str);
		return temp;
	}

	myString operator+(const myString& str) {
		myString temp;
		temp._length = _length + str._length;
		temp._data = new char[temp._length + 1];
		temp._data = _strcat(_data, str._data);
		return temp;
	}

	typedef char* iterator;
	iterator begin() {
		return _data;
	}
	iterator end() {
		return _data + _length;
	}

	char& operator[](size_t pos) {
		if (pos < _length) {
			return _data[pos];
		}
		else  throw "Index out of range";
	}

	const char* c_str() const {
		return _data;
	}

	std::string to_string() const {
		return std::string(_data);
	}

	size_t find(char ch, size_t start = 0, size_t end = 0) {
		if (end >= _length || start > end) throw "访问非法地址";

		for (size_t i = start; i < end; i++) {
			if (_data[i] == ch) {
				return i;
			}
		}
		return std::string::npos;
	}


	bool operator==(const myString& str) const {
		return _strcmp(_data, str._data) == 0;
	}

	//strcmp函数返回值为0时，表示两个字符串相等

	bool operator!=(const myString& str) const {
		return ~_strcmp(_data, str._data) != 0;
	}

	bool operator==(const char* str) const {
		return _strcmp(_data, str) == 0;
	}

	bool operator!=(const char* str) const {
		return ~_strcmp(_data, str) != 0;
	}

	bool operator<(const myString& str) const {
		return _strcmp(_data, str._data) < 0;
	}
	//NOTICE!!!
	//使用myString作为std::map和std::set的键。在这些数据结构中，键是需要进行比较的。以下是你的代码中进行字符串比较的地方：
	//在dijkstra1函数中，你创建了一个std::map，其键类型为myString。在你使用operator[]，insert或count成员函数时，std::map需要比较键来确定元素的位置或是否存在某个键。
	//在dijkstra1函数中，你创建了一个std::set，其元素类型为myString。在你使用insert或count成员函数时，std::set需要比较元素来确定元素的位置或是否存在某个元素。
	//在tranTOmatrix函数中，你创建了一个std::map，其键类型为std::pair<myString, myString>。在你使用operator[]成员函数时，std::map需要比较键来确定元素的位置。std::pair的比较运算符会比较其两个元素，所以这里也会比较myString对象。
	//以上这些地方都会隐式地调用myString的比较运算符。如果myString的比较运算符没有实现或实现不正确，那么这些操作可能会导致未定义的行为，包括死循环。


	friend std::ostream& operator<<(std::ostream& os, const myString& str) {
		os << str._data;
		return os;
	}


	std::string toString() const {
		return std::string(_data);
	}

	friend std::istream& operator>>(std::istream& is, myString& str) {
		char buffer[256];
		is >> buffer;
		str._data = _strcpy(str._data, buffer);
		return is;
	}

	friend myString operator+(const char* str1, const myString& str2) {
		myString temp;
		temp._length = _strlen(str1) + str2._length;
		temp._data = new char[temp._length + 1];
		temp._data = _strcat(const_cast<char*>(str1), str2._data);
		return temp;
	}

	friend myString operator+(const char ch, const myString& str) {
		myString temp;
		temp._length = 1 + str._length;
		temp._data = new char[temp._length + 1];
		temp._data[0] = ch;
		temp._data = _strcat(temp._data, str._data);
		return temp;
	}

	friend std::istream& getline(std::istream& is, myString& str) {
		char buffer[256];
		is.getline(buffer, sizeof(buffer));
		str._data = _strcpy(str._data, buffer);
		return is;
	}

	int to_int() {
		int res = 0;
		for (size_t i = 0; i < _length; i++) {
			res = res * 10 + _data[i] - '0';
		}
		return res;
	}

};

//int to_int(const char* data) {
//	int res = 0;
//	for (size_t i = 0; i < _strlen(data); i++) {
//		res = res * 10 + data[i] - '0';
//	}
//	return res;
//}
//
//namespace std {
//	template<>
//	struct hash<myString> {
//		std::size_t operator()(const myString& s) const noexcept {
//			// 使用 std::hash<std::string> 来计算 myString 的哈希值
//			return std::hash<std::string>{}(s.c_str());
//		}
//	};
//
//	template<>
//	struct equal_to<myString> {
//		bool operator()(const myString& lhs, const myString& rhs) const noexcept {
//			// 使用 myString 的比较运算符来比较两个 myString 是否相等
//			return lhs == rhs;
//		}
//	};
//}
//std::unordered_map试图使用std::hash<myString>和std::equal_to<myString>
// 但是这两个函数模板对于myString类型可能没有特化版本
// 你需要为myString类型提供std::hash和std::equal_to的特化版本
//定义了std::hash<myString>和std::equal_to<myString>的特化版本，使得std::unordered_map可以用于myString类型的键

