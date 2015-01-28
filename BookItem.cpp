#ifndef BOOKITEM_CPP
#define BOOKITEM_CPP
#include "BookItem.hpp"
#include <iostream>
#include <string>
using namespace std;

int BookItem::getSerialNum()
{
    return serialNum;
}

int BookItem::getYearPublished()
{
    return yearPublished;
}

int BookItem::getCopiesSold()
{
    return copiesSold;
}

string BookItem::getTitle()
{
    return title;
}

string BookItem::getAuthor()
{
    return author;
}

ostream& operator<<(ostream& os, const BookItem& s)
{
    os << "<" << s.serialNum << "> " << s.title << " : "
       << s.author << " (" << s.yearPublished << ") - "
       << s.copiesSold << " copies sold";

    return os;
}

bool operator< (BookItem& b1, BookItem& b2)
{
    return b1.copiesSold < b2.copiesSold;
}

bool operator> (BookItem& b1, BookItem& b2)
{
    if (b1.yearPublished == b2.yearPublished)
    {
        return b1.title < b2.title;
    }
    else
    {
        return b1.yearPublished > b2.yearPublished;
    }
}

#endif // BOOKITEM_CPP
