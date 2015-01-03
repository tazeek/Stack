#ifndef XSTACK_HPP
#define XSTACK_HPP
#include "Node.hpp"
#include <string>
using namespace std;

template<typename T>
class XStack
{

private:

    Node<T>* top;

public:

    XStack();

    ~XStack();

    XStack(const XStack<T>& origin);

    void push(T& Book);

    bool pop();

    bool pop(T& oldTop);

    bool peek();

    bool peek(T& peekTop);

    bool duplicate();

    void swapTop();

    bool roll(int counter);

    bool retrieveBook(int SerialNumTarget, T& getItem);

    void displaySortedBooks(XStack<T>*& sortedStack, int itemsToDisplay);

    void topSellers(XStack<T>*& sortedStack, XStack<T>*& originalStack);

    void worseSellers(XStack<T>*& sortedStack, XStack<T>*& originalStack);

    void RecentBooks(XStack<T>*& sortedStack, XStack<T>*& originalStack);

    void keywordSearch(string& key);

    void uniqueAuthors(XStack<T>*& uniqueStack, XStack<T>*& originalStack);

    bool isEmpty();

    void makeEmpty();

    void displayAllItems();

};

#endif // XSTACK_HPP

