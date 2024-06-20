#include "lib_management.h"

LibManagement::LibManagement(std::string name = "东北林业大学图书馆") : _name(name){
    _book_list = BookList();
    _reader_list = ReaderList();
}

template <typename T>
T LibManagement::_get_input(const std::string& prompt) const{
    T input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

void LibManagement::lib_management(){
    while(true){
        system("cls");
        std::cout << "欢迎来到" << _name << "！" << std::endl;
        std::cout << "1. 图书管理" << std::endl;
        std::cout << "2. 读者管理" << std::endl;
        std::cout << "3. 借还管理" << std::endl;
        std::cout << "4. 退出" << std::endl;
        int choice = _get_input<int>("请输入您的选择：");
        switch(choice){
            case 1:
                _book_list.book_management();
                break;
            case 2:
                _reader_list.reader_management();
                break;
            case 3:
                _reader_list.borrow_return_management();
                break;
            case 4:
                return;
            default:
                std::cout << "输入错误，请重新输入！" << std::endl;
        }
    }
    system("pause");

}

int main(){
    LibManagement lib("东北林业大学图书馆");
    lib.lib_management();
    return 0;
}