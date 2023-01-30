//
// Created by BYU CS 236 on 3/22/2021.
//

#include <iostream>
#include "BookListCreator.h"

BookListCreator::BookListCreator(std::ifstream& input) : bookCreator(input) {}

std::vector<Book*> BookListCreator::createBookList() {
    while (bookCreator.hasMoreBooksToCreate()) {
        Book* book = bookCreator.createBook();
        bookList.push_back(book);


        // TODO: Added for debugging purposes
        // std::cout << *book << " - Pages: " << book->getPages() << " - Hours: " << book->getHours() << std::endl;
    }
    return bookList;
}
