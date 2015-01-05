#ifndef XSTACK_CPP
#define XSTACK_CPP
#include <iostream>
#include <string>
#include "XStack.hpp"
#include "Node.hpp"
using namespace std;

template<typename T>
XStack<T>::XStack()
{
    top = NULL;
}

template<typename T>
XStack<T>::~XStack()
{
    makeEmpty();
}

template<typename T>
XStack<T>::XStack(const XStack<T>& origin)
{
    XStack<T>* tempo = new XStack<T>(); //a temporary stack

    top = NULL;

    Node<T>* start;

    start = origin.top;

    while (start != NULL)
    {
        tempo->push(start->info);
        start = start->next;
    }

    start = tempo->top;

    while(start != NULL)
    {
        push(start->info);
        start = start->next;
    }

    delete tempo;

}

template<typename T>
void XStack<T>::push(T& Book)
{
    Node<T>* newBook = new Node<T>;

    newBook->info = Book;
    newBook->next = top;

    top = newBook;

    return;
}

template<typename T>
bool XStack<T>::pop()
{
    if (top == NULL)
    {
        return false;
    }

    Node<T>* newTop = top;

    newTop = top->next;

    delete top;

    top = newTop;

    return true;
}

template<typename T>
bool XStack<T>::pop(T& oldTop)
{
    if ( top == NULL )
    {
        return false;
    }

    oldTop = top->info;

    Node<T>* newTop = top;

    newTop = top->next;

    delete top;

    top = newTop;

    return true;

}

template<typename T>
bool XStack<T>::peek()
{
    if (top == NULL)
    {
        return false;
    }

    return true;
}

template<typename T>
bool XStack<T>::peek(T& peekTop)
{
    if (top == NULL)
    {
        return false;
    }

    peekTop = top->info;

    return true;
}

template<typename T>
bool XStack<T>::duplicate()
{
    if (top == NULL)
    {
        return false;
    }

    Node<T>* copyTop = new Node<T>;

    copyTop->info = top->info;
    copyTop->next = top;

    top = copyTop;
    return true;
}

template<typename T>
void XStack<T>::swapTop()
{
    if (top == NULL)
    {
        return;
    }

    Node<T>* first_top = top;
    Node<T>* second_top = top->next;

    first_top->next = second_top->next;
    second_top->next = first_top;

    top = second_top;

    return;
}

template<typename T>
bool XStack<T>::roll(int counter) //ABCDE
{
    //A is the top element, let counter = 4

    Node<T>* origin = top; //This is A
    Node<T>* jump = top->next; //Start off at B

    top = jump; //B at the top

    Node<T>* start = jump->next; //the pointer that starts moving till the required count is reached

    counter = counter - 2; //A is to be placed at end & B is the starting point, 2 decremented
    int roll_counter = 1;

    while (roll_counter < counter)
    {
        roll_counter++;

        start = start->next; //3 = C, 4 = D

        if(start == NULL)
        {
            return false;
        }
    }

    origin->next = start->next; //Point A to E
    start->next = origin; //Bring A to the front

    return true;
}

template<typename T>
bool XStack<T>::retrieveBook(int SerialNumTarget, T& getItem)
{
    if (top == NULL)
    {
        return false;
    }

    Node<T>* checker = top;

    while(checker != NULL)
    {
        if(checker->info.getSerialNum() == SerialNumTarget)
        {
            getItem = checker->info;
            return true;
        }

        checker = checker->next;
    }

    cout << "\nNo such Book present with given serial number. Please try again later\n" << endl;
    return false;
}

template<typename T>
void XStack<T>::displaySortedBooks(XStack<T>*& sortedStack, int itemsToDisplay)
{
    T displayItem;

    for(int i = 0; i < itemsToDisplay; i++)
    {
        sortedStack->pop(displayItem);

        cout << displayItem << endl;

        if(sortedStack->isEmpty())
        {
            cout << "\nStack Limit reached. \n" << endl;
            return;
        }
    }

    cout << endl;
    return;
}

template<typename T>
void XStack<T>::topSellers(XStack<T>*& sortedStack, XStack<T>*& originalStack)
{
    while(!originalStack->isEmpty()) //S1 is not empty
    {
        T currentItem;
        originalStack->pop(currentItem); // x = S1.pop()

        T sortedItem;
        sortedStack->peek(sortedItem); //S2.peek()

        while((!sortedStack->isEmpty())&& (sortedItem.getCopiesSold() > currentItem.getCopiesSold())) //S2 is not empty AND S2.peek() > x
        {
            T poppedItem;

            sortedStack->pop(poppedItem);

            originalStack->push(poppedItem); //S1.push(S2.pop())

            sortedStack->peek(sortedItem);
        }

        sortedStack->push(currentItem); //S2.push(x);
    }
}

template<typename T>
void XStack<T>::worseSellers(XStack<T>*& sortedStack, XStack<T>*& originalStack)
{
    while(!originalStack->isEmpty()) //S1 is not empty
    {
        T currentItem;
        originalStack->pop(currentItem); // x = S1.pop()

        T sortedItem;
        sortedStack->peek(sortedItem); //S2.peek()

        while((!sortedStack->isEmpty())&& (sortedItem < currentItem)) //S2 is not empty AND S2.peek() < x
        {
            T poppedItem;

            sortedStack->pop(poppedItem);

            originalStack->push(poppedItem); //S1.push(S2.pop())

            sortedStack->peek(sortedItem);
        }

        sortedStack->push(currentItem); //S2.push(x);
    }

    return;
}

template<typename T>
void XStack<T>::RecentBooks(XStack<T>*& sortedStack, XStack<T>*& originalStack)
{
    while(!originalStack->isEmpty()) //S1 is not empty
    {
        T currentItem;
        originalStack->pop(currentItem); // x = S1.pop()

        T sortedItem;
        sortedStack->peek(sortedItem); //S2.peek()

        while((!sortedStack->isEmpty())&& (sortedItem > currentItem)) //S2 is not empty AND S2.peek() > x
        {
            T poppedItem;

            sortedStack->pop(poppedItem);

            originalStack->push(poppedItem); //S1.push(S2.pop())

            sortedStack->peek(sortedItem);
        }

        sortedStack->push(currentItem); //S2.push(x);
    }

    return;
}

template<typename T>
void XStack<T>::keywordSearch(string& key)
{
    string title_search;

    string lower_keyWord = key;
    string upper_keyWord = key;

    lower_keyWord[0] = tolower(lower_keyWord[0]);
    upper_keyWord[0] = toupper(upper_keyWord[0]);

    Node<T>* searching = top;
    int found = 0;

    cout << endl;

    while (searching != NULL)
    {
        title_search = searching->info.getTitle();

        size_t sop = title_search.find(lower_keyWord);
        size_t pos = title_search.find(upper_keyWord);


        if((sop != string::npos) ||(pos != string::npos))
        {
            cout << searching->info << endl;
            found = 1;
        }


        searching = searching->next;
    }

    if(found == 0)
    {
        cout << "No book found. Please try again later.\n";
    }

    cout << endl;

    return;
}

template<typename T>
void XStack<T>::uniqueAuthors(XStack<T>*& uniqueStack, XStack<T>*& originalStack)
{
    //Required: Two more stacks, Two variables, 1 Comparison, 2 Bools

    XStack<T>* temporary = new XStack<T>();
    XStack<T>* not_unique = new XStack<T>(); //used to store items which are not unique

    bool not_one; //This is to check whether the Author is unique or not
    bool cross; //This is to check whether the top item is unique or not, hence result in crossing out or not

    string X;
    string Y;

    T top_check;
    T second_check;

    while (!originalStack->isEmpty())
    {
        cross = false;
        originalStack->pop(top_check);

        XStack<T>* temp_original = new XStack<T>(*originalStack); //a temporary copy of the original

        X = top_check.getAuthor(); //Gets name of Author

        while (!temp_original->isEmpty())
        {
            not_one = false;

            temp_original->pop(second_check);
            Y = second_check.getAuthor(); //Gets name of Author of the next book

            if(X == Y) //Compare the names of X and Y
            {
                not_one = true; //Indicates that there is another copy
                cross = true; //Indicates that X should not be stored in unique stack

                not_unique->push(second_check); //stores copy in this stack
            }

            if(not_one == false)
            {
                temporary->push(second_check); //stores a 'unique' copy in this temporary stack
            }
        }

        Node<T>* ptr = not_unique->top;

        while(ptr != NULL)
        {
            if(X == ptr->info.getAuthor())
            {
                cross = true;
                break;
            }

            ptr = ptr->next;
        }

        if (cross == true) //if the top book is not unique
        {
            not_unique->push(top_check); //stores it into this stack
        }

        else
        {
            uniqueStack->push(top_check); //stores it into the unique stack
        }

    }

    XStack<T>* topUnRepeated = new XStack<T>();
    XStack<T>* sorted_notUnique = new XStack<T>();
    int check;

    topUnRepeated->topSellers(sorted_notUnique, not_unique);

    while(!sorted_notUnique->isEmpty())
    {
        check = 0; //used as boolean alternative
        sorted_notUnique->pop(top_check); //checks the top book in sorted stack
        X = top_check.getAuthor(); //gets author of top book

        Node<T>* ptr = topUnRepeated->top;

        while(ptr != NULL)
        {
            if(X == ptr->info.getAuthor()) //if author of top book is repeated in this stack
            {
                not_unique->push(top_check);
                check = 1;
            }

            ptr = ptr->next;
        }

        if(check == 0) //if author is not same
        {
            topUnRepeated->push(top_check);
        }
    }

    while(!topUnRepeated->isEmpty())
    {
        topUnRepeated->pop(top_check);
        uniqueStack->push(top_check);
    }

    delete not_unique;

    return;
}

template<typename T>
bool XStack<T>::isEmpty()
{
    return top == NULL;
}

template<typename T>
void XStack<T>::makeEmpty ()
{

    Node<T>* begin = top;

    while (top != NULL)
    {
        begin = top;
        top = top->next;
        delete begin;
    }

    top = NULL;

    return;
}

template<typename T>
void XStack<T>::displayAllItems()
{

    Node<T>* displayer = top;

    while (displayer != NULL)
    {
        cout << displayer->info << endl;
        displayer = displayer->next;
    }

    cout << endl;

    return;
}

#endif // XSTACK_CPP

