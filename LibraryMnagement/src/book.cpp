#include "book.h"


Book::Book(int id, const std::string& name, const std::string& author)
    : _book_id(id), _book_name(name), _book_author(author) {}

int Book::get_book_id() const {
    return _book_id;
}

std::string Book::get_book_name() const {
    return _book_name;
}

std::string Book::get_author() const {
    return _book_author;
}

BookList::BookList() {
    _book_list = std::vector<Book>();
}

BookList::~BookList() {
    _book_list.clear();
}

void BookList::load_books() {
    std::ifstream file(BOOK_FILE_NAME);
    if (!file) {
        std::cerr << "Error opening file: " << BOOK_FILE_NAME << "\n";
        return;
    }
    if (file.is_open()) {
        int id;
        std::string name, author;
        while (file >> id >> name >> author) {
            _book_list.emplace_back(id, name, author);
            //emplace_back()函数是C++11的新特性，用于在容器末尾直接构造对象
            //相较于push_back(Book(id, name, author))，emplace_back()少了一次拷贝构造
        }
        file.close();
    }
}

void BookList::save_books() const {
    std::ofstream file(BOOK_FILE_NAME);
    if (!file) {
        std::cerr << "Error opening file: " << BOOK_FILE_NAME << "\n";
        return;
    }
    if (file.is_open()) {
        for (const auto& book : _book_list) {
            file << book.get_book_id() << " "
                << book.get_book_name() << " "
                << book.get_author() << "\n";
        }
        file.close();
    }
}

std::vector<Book> BookList::get_book_list() const {
    return _book_list;
}

void BookList::add_book(const Book& new_book) {
    _book_list.push_back(new_book);
}

void BookList::delete_book(int id) {
    _book_list.erase(
        std::remove_if(_book_list.begin(), _book_list.end(),
            [id](const Book& book) { return book.get_book_id() == id; }),
        _book_list.end());
    //erase(first,last);删除从first到last之间的字符（first和last都是迭代器）
    //remove_if(iterator begin, iterator end, UnaryPredicate p)
    //UnaryPredicate p 是一个一元函数，接受一个参数，返回bool类型，此处是lambda表达式,如果回调函数返回为真，则将当前所指向的参数移到尾部
    //[id](const Book& book) { return book.get_book_id() == id; } 是lambda表达式，[id]是捕获列表
    //捕获列表[id]表示在lambda表达式中可以使用id这个变量，捕获列表还可以是[=]表示以传值方式捕获所有局部变量，[&]表示以引用方式捕获所有局部变量

    //这部分的代码首先检查book_list.begin()到book_list.end()中book.get_book_id() == id的元素，然后将这些元素移到尾部，最后erase删除尾部的元素
}

void BookList::delete_book(const std::string& name) {
    _book_list.erase(
        std::remove_if(_book_list.begin(), _book_list.end(),
            [&name](const Book& book) { return book.get_book_name() == name; }),
        _book_list.end());
    //同上
}

Book BookList::search_book(int id) const {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [id](const Book& book) { return book.get_book_id() == id; });
    //find_if(iterator begin, iterator end, UnaryPredicate p)
    //UnaryPredicate p 是一个一元函数，接受一个参数，返回bool类型，此处是lambda表达式
    //如果回调函数返回为真，则返回当前所指向的参数
    if (it != _book_list.end()) {
        return *it;
    }
    else {
        std::cout << "Book not found\n";
        return Book(0, "", "");
    }
}

Book BookList::search_book(const std::string& name) const {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [&name](const Book& book) { return book.get_book_name() == name; });
    //同上
    if (it != _book_list.end()) {
        return *it;
    }
    else {
        std::cout << "Book not found\n";
        return Book(0, "", "");
    }
}

void BookList::revise_book(int id) {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [id](const Book& book) { return book.get_book_id() == id; });
    //同上
    if (it != _book_list.end()) {
        int new_id = _get_input<int>("请输入新的书号: ");
        std::string new_name = _get_input<std::string>("请输入新的书名: ");
        std::string new_author = _get_input<std::string>("请输入新的作者: ");
        *it = Book(new_id, new_name, new_author);
    }
    else {
        std::cout << "Book not found\n";
    }
}

void BookList::revise_book(const std::string& name) {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [&name](const Book& book) { return book.get_book_name() == name; });
    //同上
    if (it != _book_list.end()) {
        int new_id = _get_input<int>("请输入新的书号: ");
        std::string new_name = _get_input<std::string>("请输入新的书名: ");
        std::string new_author = _get_input<std::string>("请输入新的作者: ");
        *it = Book(new_id, new_name, new_author);
    }
    else {
        std::cout << "Book not found\n";
    }
}

void BookList::show_book_list() const {
    for (const auto& book : _book_list) {
        display_book(book);
    }
}

void BookList::display_book(const Book& book) const {
    std::cout << "书籍序号: " << book.get_book_id() << "\n"
        << "书籍名字: " << book.get_book_name() << "\n"
        << "书籍作者: " << book.get_author() << "\n";
}

template <typename T>
T BookList::_get_input(const std::string& prompt) const {
    std::cout << prompt;
    T value;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cin.clear(); // 清除错误标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略之前留在输入流中的字符
        std::cout << "Invalid input. Please try again: ";
        std::cin >> value;
    }
    return value;
    //这个函数是一个模板函数，用于获取用户输入的值，T是模板参数，可以是任意类型，避免了重复IO操作代码
}

std::any BookList::_get_any_input() const{
    std::any value;
    std::string input; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略之前留在输入流中的换行符
    std::getline(std::cin, input); // 读取整行输入

    // 尝试将输入转换为整数
    try {
        int intValue = std::stoi(input);
        value = intValue; // 如果成功，存储为int
    }
    catch (const std::invalid_argument& e) {
        // 如果转换失败，假定输入是字符串
        value = input; // 存储为string

    }
    return value;
}


void BookList::book_management() {
    
    //std::unique_ptr<T>是一个智能指针，用于管理动态分配的对象，当unique_ptr对象离开作用域时，它所指向的对象会被自动释放
    //unique_ptr对象不能被复制，只能被移动，这样可以避免内存泄漏
    //unique_ptr对象的析构函数会自动释放所指向的对象

    load_books();
    while (true) {
        system("cls");
        std::cout << "1. 添加书籍\n";
        std::cout << "2. 删除书籍\n";
        std::cout << "3. 查找书籍\n";
        std::cout << "4. 修改书籍\n";
        std::cout << "5. 显示书籍列表\n";
        std::cout << "6. 退出图书管理\n";
        std::cout << "请选择操作：";
        int choice;
        std::cin >> choice;


        switch (choice) {
            //相较于c++中的std::endl，\n更快，因为std::endl会刷新缓冲区
        case 1: {
            int id = _get_input<int>("请输入书籍序号：");
            std::string name = _get_input<std::string>("请输入书籍名称：");
            std::string author = _get_input<std::string>("请输入作者：");
            add_book(Book(id, name, author));
            break;
        }
        case 2: {
            std::cout << "请输入要删除的书籍序号或者书籍名称: ";
            std::any value = _get_any_input();
            if (value.has_value()) {
                if (value.type() == typeid(int)) {
                    int id = std::any_cast<int>(value);
                    delete_book(id);
                }
                else if (value.type() == typeid(std::string)) {
                    std::string name = std::any_cast<std::string>(value);
                    delete_book(name);
                }
                //std::any_cast<T>用于将std::any对象转换为T类型，显示转换
                else {
                    std::cerr << "Unsupported type for deleting book" << std::endl;
                }
            }
            else {
                std::cout << "No value provided for deleting book" << std::endl;
            }
            break;
        }
        case 3: {
            Book book(0, "", "");
            std::cout << "请输入要查找的书籍序号或者书籍名称: ";
            std::any value = _get_any_input();
            if (value.has_value()) {
                if (value.type() == typeid(int)) {
                    int id = std::any_cast<int>(value);
                    book = search_book(id);
                }
                else if (value.type() == typeid(std::string)) {
                    std::string name = std::any_cast<std::string>(value);
                    book = search_book(name);
                }
                else {
                    std::cerr << "Unsupported type for book" << std::endl;
                }
                display_book(book);
            }
            else {
                std::cout << "No value provided for book" << std::endl;
            }
            break;
        }
        case 4: {
            std::cout << "请输入要修改的书籍序号或者书籍名称: ";
            std::any value = _get_any_input();
            if (value.has_value()) {
                if (value.type() == typeid(int)) {
                    int id = std::any_cast<int>(value);
                    std::cout << id << std::endl;
                    revise_book(id);
                }
                else if (value.type() == typeid(std::string)) {
                    std::string name = std::any_cast<std::string>(value);
                    revise_book(name);
                }
                else {
                    std::cerr << "Unsupported type for book" << std::endl;
                }
            }
            else {
                std::cout << "No value provided for book" << std::endl;
            }
            break;
        }
        //这里使用了std::any，可以存储任意类型的值，减少了IO操作
        case 5: {
            show_book_list();
            break;
        }
        case 6: {
            save_books();
            return;
            break;
        }
        default: {
            std::cout << "Invalid action\n";
            break;
        }
        }
        //可以使用std::map<int, std::function<void()>> commands;代替switch-case语句
        //但是这样做对代码没有优化而且难以阅读
        system("pause");
    }
}

