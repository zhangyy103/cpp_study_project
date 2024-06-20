#ifndef LIB_MANAGEMENT_H
#define LIB_MANAGEMENT_H

#include "book.h"
#include "reader.h"

class LibManagement{
    private:
        BookList _book_list;
        ReaderList _reader_list;
        std::string _name = "";
        template <typename T>
        T _get_input(const std::string& prompt) const;
    public:
        LibManagement(std::string name);
        void lib_management();
};


#endif