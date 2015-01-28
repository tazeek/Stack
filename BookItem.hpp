#ifndef BOOKITEM_HPP
#define BOOKITEM_HPP
#include <iostream>
#include <string>
using namespace std;

class BookItem
{
    int serialNum;
    string title;
    string author;
    int yearPublished;
    int copiesSold;

public:

    BookItem(int serialNum=0, string title="", string ath="", int year=0, int copiesSold=0)
    : serialNum(serialNum), title(title), author(ath), yearPublished(year), copiesSold(copiesSold) { }

    int getSerialNum();

    int getYearPublished();

    int getCopiesSold();

    string getTitle();

    string getAuthor();

	friend ostream& operator<<(ostream& os, const BookItem& s);

	friend bool operator< (BookItem& b1, BookItem& b2);

	friend bool operator> (BookItem& b1, BookItem& b2);
};


#endif // BOOKITEM_HPP
