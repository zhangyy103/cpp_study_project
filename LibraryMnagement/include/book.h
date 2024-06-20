#ifndef BOOK_H
#define BOOK_H

#define BOOK_FILE_NAME "../assets/book_list.txt"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <any>

class Book {
private:
    int _book_id;
    std::string _book_name;
    std::string _book_author;

public:
    Book(int, const std::string&, const std::string&);
    int get_book_id() const;
    std::string get_book_name() const;
    std::string get_author() const;

};

class BookList {
private:
    std::vector<Book> _book_list;

    //void display_book(const Book&) const;

    template <typename T>
    T _get_input(const std::string& prompt) const;

    std::any _get_any_input() const;

public:
    BookList();
    ~BookList();
    void load_books();
    void save_books() const;
    std::vector<Book> get_book_list() const;
    void add_book(const Book&);
    void delete_book(int);
    void delete_book(const std::string&);
    Book search_book(int) const;
    Book search_book(const std::string&) const;
    void revise_book(int);
    void revise_book(const std::string&);
    void show_book_list() const;

    void display_book(const Book& book) const;
    void book_management();
};


#endif