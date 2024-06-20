#include "reader.h"

Reader::Reader(const std::string& name, int id, const std::string& phone, const BookList& borrowed_books) 
    : _name(name), _id(id), _phone(phone), _borrowed_books(borrowed_books) {}

std::string Reader::get_name() const {
    return _name;
}

int Reader::get_id() const {
    return _id;
}

std::string Reader::get_phone() const {
    return _phone;
}

BookList Reader::get_borrowed_books() const {
    return _borrowed_books;
}

void Reader::borrow_book(const Book& book) {
    _borrowed_books.add_book(book);
}

void Reader::return_book(const Book& book) {
    auto it = std::find_if(_borrowed_books.get_book_list().begin(), _borrowed_books.get_book_list().end(), 
        [&book](const Book& b) { return b.get_book_id() == book.get_book_id(); });

    if (it != _borrowed_books.get_book_list().end()) {
        _borrowed_books.delete_book(book.get_book_id());
    }
    else {
        std::cout << _name <<"has not borrowed this book\n";
    }
}

ReaderList::ReaderList() {
    std::ifstream file(READER_FILE_NAME);
    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines
        // Parse reader info
        BookList borrowed_books;
        std::string name = line;
        getline(file, line);
        std::string id = line;
        getline(file, line);
        std::string phone = line;
        // Parse books
        while (getline(file, line) && line != "*") {
            int book_id = std::stoi(line);
            getline(file, line);
            std::string book_name = line;
            getline(file, line);
            std::string book_author = line;
            Book book(book_id, book_name, book_author);
            borrowed_books.add_book(book);
        }
        Reader reader(name, std::stoi(id), phone, borrowed_books);
        _reader_list.push_back(reader);
    }
}

ReaderList::~ReaderList() {
    std::ofstream file(READER_FILE_NAME);
    if (!file) {
        std::cerr << "Error opening file: " << READER_FILE_NAME << "\n";
        return;
    }
    if (file.is_open()) {
        for (const auto& reader : _reader_list) {
            file << reader.get_name() << "\n"
                << reader.get_id() << "\n"
                << reader.get_phone() << "\n";
            for (const auto& book : reader.get_borrowed_books().get_book_list()) {
                file << book.get_book_id() << "\n"
                    << book.get_book_name() << "\n"
                    << book.get_author() << "\n";
            }
            file << "*\n";
        }
        file.close();
    }
}

void ReaderList::add_reader(const Reader& new_reader) {
    _reader_list.push_back(new_reader);
}

void ReaderList::delete_reader(const std::string& name) {
    auto it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [&name](const Reader& reader) { return reader.get_name() == name; });

    if (it != _reader_list.end()) {
        _reader_list.erase(it);
    }
    else {
        std::cout << "Reader not found\n";
    }
}

void ReaderList::delete_reader(int id) {
    auto it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [id](const Reader& reader) { return reader.get_id() == id; });

    if (it != _reader_list.end()) {
        _reader_list.erase(it);
    }
    else {
        std::cout << "Reader not found\n";
    }
}

Reader ReaderList::search_reader(const std::string& name) const {
    auto it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [&name](const Reader& reader) { return reader.get_name() == name; });

    if (it != _reader_list.end()) {
        return *it;
    }
    else {
        std::cout << "Reader not found\n";
        return Reader("", 0, "", BookList());
    }
}

Reader ReaderList::search_reader(int id) const {
    auto it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [id](const Reader& reader) { return reader.get_id() == id; });

    if (it != _reader_list.end()) {
        return *it;
    }
    else {
        std::cout << "Reader not found\n";
        return Reader("", 0, "", BookList());
    }
}

void ReaderList::revise_reader(const std::string& name) {
    auto it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [&name](const Reader& reader) { return reader.get_name() == name; });

    if (it != _reader_list.end()) {
        std::string new_name = _get_input<std::string>("请输入修改后的名字：");
        int new_id = _get_input<int>("请输入修改后的ID：");
        std::string new_phone = _get_input<std::string>("请输入修改后的电话：");
        *it = Reader(new_name, new_id, new_phone, it->get_borrowed_books());
    }
    else {
        std::cout << "Reader not found\n";
    }
}

void ReaderList::revise_reader(int id) {
    auto it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [id](const Reader& reader) { return reader.get_id() == id; });

    if (it != _reader_list.end()) {
        std::string new_name = _get_input<std::string>("请输入修改后的名字：");
        int new_id = _get_input<int>("请输入修改后的ID：");
        std::string new_phone = _get_input<std::string>("请输入修改后的电话：");
        *it = Reader(new_name, new_id, new_phone, it->get_borrowed_books());
    }
    else {
        std::cout << "Reader not found\n";
    }
}

void ReaderList::show_reader_list() const {
    for (const auto& reader : _reader_list) {
        display_reader(reader);
    }
}

void ReaderList::display_reader(const Reader& reader) const {
    std::cout << "姓名：" << reader.get_name() << "\n"
        << "ID: " << reader.get_id() << "\n"
        << "电话：" << reader.get_phone() << "\n"
        << "借阅的书籍: \n";
    reader.get_borrowed_books().show_book_list();
    std::cout << "\n";
}

template <typename T>
T ReaderList::_get_input(const std::string& prompt) const {
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

std::any ReaderList::_get_any_input() const{
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

void ReaderList::reader_management() {

    while (true){
        system("cls");
        std::cout << "1. 添加读者\n";
        std::cout << "2. 删除读者\n";
        std::cout << "3. 查找读者\n";
        std::cout << "4. 修改读者\n";
        std::cout << "5. 显示读者列表\n";
        std::cout << "6. 退出读者管理\n";
        std::cout << "请选择操作：";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name = _get_input<std::string>("请输入读者姓名：");
                int id = _get_input<int>("请输入读者ID:");
                std::string phone = _get_input<std::string>("请输入读者电话：");
                Reader new_reader(name, id, phone, BookList());
                add_reader(new_reader);
                break;
            }
            case 2: {
                std::cout << "请输入要删除的读者序号或者读者名称: ";
                std::any value = _get_any_input();
                if (value.has_value()) {
                    if (value.type() == typeid(int)) {
                        int id = std::any_cast<int>(value);
                        delete_reader(id);
                    }
                    else if (value.type() == typeid(std::string)) {
                        std::string name = std::any_cast<std::string>(value);
                        delete_reader(name);
                    }
                    //std::any_cast<T>用于将std::any对象转换为T类型，显示转换
                    else {
                        std::cerr << "Unsupported type for deleting reader" << std::endl;
                    }
                }
                else {
                    std::cout << "No value provided for deleting reader" << std::endl;
                }
                break;
            }
            case 3:{
                Reader reader("", 0, "", BookList());
                std::cout << "请输入要查找的读者序号或者读者名称: ";
                std::any value = _get_any_input();
                if (value.has_value()) {
                    if (value.type() == typeid(int)) {
                        int id = std::any_cast<int>(value);
                        reader = search_reader(id);
                    }
                    else if (value.type() == typeid(std::string)) {
                        std::string name = std::any_cast<std::string>(value);
                        reader = search_reader(name);
                    }
                    //std::any_cast<T>用于将std::any对象转换为T类型，显示转换
                    else {
                        std::cerr << "Unsupported type for searching reader" << std::endl;
                    }
                    display_reader(reader);
                }
                else {
                    std::cout << "No value provided for searching reader" << std::endl;
                }
                break;
            }
            case 4:{
                std::cout << "请输入要修改的读者序号或者读者名称: ";
                std::any value = _get_any_input();
                if (value.has_value()) {
                    if (value.type() == typeid(int)) {
                        int id = std::any_cast<int>(value);
                        revise_reader(id);
                    }
                    else if (value.type() == typeid(std::string)) {
                        std::string name = std::any_cast<std::string>(value);
                        revise_reader(name);
                    }
                    //std::any_cast<T>用于将std::any对象转换为T类型，显示转换
                    else {
                        std::cerr << "Unsupported type for revising reader" << std::endl;
                    }
                }
                else {
                    std::cout << "No value provided for revising reader" << std::endl;
                }
                break;
            }

            case 5:{
                show_reader_list();
                break;
            }

            case 6:{
                return;
            }
        }
        system("pause");
    }
    
}

void ReaderList::borrow_return_management() {
    std::cout<<"请输入操作的读者姓名或者序号：";
    std::any value = _get_any_input();
    auto it = _reader_list.end();
    if (value.has_value()) {
        if (value.type() == typeid(int)) {
            int id = std::any_cast<int>(value);
            it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [id](const Reader& reader) { return reader.get_id() == id; });
        }
        else if (value.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(value);
            it = std::find_if(_reader_list.begin(), _reader_list.end(), 
        [name](const Reader& reader) { return reader.get_name() == name; });
        }
    }
    if(it == _reader_list.end()){
        std::cout<<"Reader not found";
        return;
    }
    while (true) {
        system("cls");
        std::cout << "1. 借书\n";
        std::cout << "2. 还书\n";
        std::cout << "3. 退出\n";
        std::cout << "请选择操作：";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "请输入要借阅的书籍序号或者书籍名称: ";
                std::any value = _get_any_input();
                if (value.has_value()) {
                    if (value.type() == typeid(int)) {
                        int book_id = std::any_cast<int>(value);
                        std::unique_ptr<BookList> book_list = std::make_unique<BookList>();
                        book_list->load_books();
                        Book book = book_list->search_book(book_id);
                        if (book.get_book_id() != 0) {
                            it -> borrow_book(book);
                        }
                    else if (value.type() == typeid(std::string)) {
                        std::unique_ptr<BookList> book_list = std::make_unique<BookList>();
                        std::string book_name = std::any_cast<std::string>(value);
                        book_list->load_books();
                        Book book = book_list->search_book(book_name);
                        if (book.get_book_id() != 0) {
                            it -> borrow_book(book);
                        }
                    }
                    else {
                        std::cerr << "Unsupported type for borrowing book" << std::endl;
                    }
                }
                else {
                    std::cout << "No value provided for borrowing book" << std::endl;
                }
                break;
                }
            }
            case 2: {
                std::cout << "请输入要归还的书籍序号或者书籍名称: ";
                std::any value = _get_any_input();
                if (value.has_value()) {
                    if (value.type() == typeid(int)) {
                        int id = std::any_cast<int>(value);
                        Book book = it -> get_borrowed_books().search_book(id);
                        if (book.get_book_id() != 0) {
                            it -> return_book(book);
                        }
                    }
                    else if (value.type() == typeid(std::string)) {
                        std::string name = std::any_cast<std::string>(value);
                        Book book = it-> get_borrowed_books().search_book(name);
                        if (book.get_book_id() != 0) {
                            it -> return_book(book);
                        }
                    }
                    else {
                        std::cerr << "Unsupported type for returning book" << std::endl;
                    }
                }
                else {
                    std::cout << "No value provided for returning book" <<std::endl;
                }
            }
            case 3:{
                return;
            }
        }
        system("pause");
    }
}