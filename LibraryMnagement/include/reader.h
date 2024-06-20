#ifndef _READER_H
#define _READER_H

#define READER_FILE_NAME "../assets/reader_list.txt"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <any>
#include <memory>
#include "book.h"

class Reader {
    private:
        std::string _name;
        int _id;
        std::string _phone;
        BookList _borrowed_books;
    
    public:
        Reader(const std::string&, int, const std::string&, const BookList&);
        std::string get_name() const;
        int get_id() const;
        std::string get_phone() const;
        BookList get_borrowed_books() const;
        void borrow_book(const Book&);
        void return_book(const Book&);

};


class ReaderList {
    private:
        std::vector<Reader> _reader_list;

        template <typename T>
        T _get_input(const std::string& prompt) const;

        std::any _get_any_input() const;

    public:
        ReaderList();
        ~ReaderList();
        void add_reader(const Reader&);
        void delete_reader(const std::string&);
        void delete_reader(int);
        Reader search_reader(const std::string&) const;
        Reader search_reader(int) const;
        void revise_reader(const std::string&);
        void revise_reader(int);
        void show_reader_list() const;

        void display_reader(const Reader& reader) const;
        void reader_management();
        void borrow_return_management();
};










#endif