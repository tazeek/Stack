#ifndef MAIN_CPP
#define MAIN_CPP
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "BookItem.hpp"
#include "XStack.hpp"
#include "XStack.cpp"
using namespace std;

void readData(const char* filename, XStack<BookItem>*& stBooks)
 {
    string line;
    ifstream ifs(filename);

    if (ifs.is_open())
        {

            //cout << "Reading data...\n";
            int c = 0;

            while ( getline (ifs,line) && (*line.c_str() != '\0') )
            {

                string delimiter = ",";
                size_t pos = 0;
                string* token = new string[5];
                int f = -1;

                while ((pos = line.find(delimiter)) != string::npos)
                {

                    token[++f] = line.substr(0, pos);
                    //cout << " " << token[f] << " | " ;
                    line.erase(0, pos + delimiter.length());
                }

                token[++f] = line;
                //cout << token[f] << endl;       // last item in string
                c++;

                // push to stack (numerical data converted to int)
                BookItem b(atoi(token[0].c_str()), token[1], token[2], atoi(token[3].c_str()), atoi(token[4].c_str()));
                stBooks->push(b);
            }

            //cout << c << " row(s) read." << endl;
            ifs.close();
        }

    else
        cout << "Unable to open file\n" << endl;
}

void PlayStack()
{
    XStack<BookItem>* NewStack = new XStack<BookItem>();
    readData("db_small.txt", NewStack);

    int option_stack;

    do
    {
        cout << "\nOptions: \n"
             << "\n1: Duplicate Top Item\n"
             << "2: Exchange the position of the two top most items on the stack\n"
             << "3: Roll n top-most items on the stack (n is a positive integer)\n"
             << "\nEnter any other number to go back to main menu\n"
             << "\nEnter your option: ";
        cin >> option_stack;

        switch(option_stack)
        {
            case 1:
                {
                    XStack<BookItem>* duplicateStack = new XStack<BookItem>(*NewStack);

                    cout << "\nBefore action: \n";
                    NewStack->displayAllItems();

                    duplicateStack->duplicate();

                    cout << "\nAfter action: \n";
                    duplicateStack->displayAllItems();

                    delete duplicateStack;

                    system("PAUSE");

                    system("CLS");

                    break;
                }

            case 2:
                {
                    XStack<BookItem>* swapStack = new XStack<BookItem>(*NewStack);

                    cout << "\nBefore action: \n";
                    NewStack->displayAllItems();

                    swapStack->swapTop();

                    cout << "\nAfter action: \n";
                    swapStack->displayAllItems();

                    delete swapStack;

                    system("PAUSE");

                    system("CLS");

                    break;
                }

            case 3:
                {
                    int roller;
                    bool allowRoll;

                    cout << "Enter the number of items to roll: ";
                    cin >> roller;

                    while(roller < 0)
                    {
                        cout << "\nCannot accept negative number. Please enter a positive integer: ";
                        cin >> roller;
                    }

                    XStack<BookItem>* rollStack = new XStack<BookItem>(*NewStack);
                    allowRoll = rollStack->roll(roller);

                    if(allowRoll)
                    {
                        cout << "\nBefore action: \n";
                        NewStack->displayAllItems();

                        cout << "\nAfter action: \n";
                        rollStack->displayAllItems();
                    }
                    else
                    {
                        cout << "\nCannot perform action, due to number entered being more than the stack items\n";
                    }

                    delete rollStack;

                    system("PAUSE");

                    system("CLS");

                    break;
                }

        }

    } while(option_stack >= 1 && option_stack <= 3);

    delete NewStack;

    return;
}

void BookStatistics()
{
    XStack<BookItem>* NewStack = new XStack<BookItem>();
    readData("db_small.txt", NewStack);

    int option_book;

    do
    {
        cout << "\nOptions: \n"
             << "\n1: Search for a book using by entering 5-digit book serial number\n"
             << "2: View the Top 5 Best Sellers\n"
             << "3: View the Bottom 5 Worse Sellers\n"
             << "4: View Top 10 Newest Books\n"
             << "5: Search for book(s) using a specific keyword\n"
             << "6: View Top n unique authors (n is a positive integer)\n"
             << "\nEnter any other number to go back to main menu\n"
             << "\nEnter your option: ";
        cin >> option_book;

        switch(option_book)
        {

        case 1:
            {
                 int serial_number;
                 cout << "\nEnter 5-digit serial number: ";
                 cin >> serial_number;

                 BookItem retrive;
                 bool retrive_success = NewStack->retrieveBook(serial_number, retrive);

                 if(retrive_success)
                 {
                     cout << retrive << endl;
                 }

                 system("PAUSE");

                 system("CLS");

                 break;
            }

        case 2:
            {
                XStack<BookItem>* SortStack = new XStack<BookItem>();
                XStack<BookItem>* TempStack = new XStack<BookItem>(*NewStack);

                NewStack->topSellers(SortStack, TempStack);

                NewStack->displaySortedBooks(SortStack, 5);

                delete SortStack;
                delete TempStack;

                system("PAUSE");

                system("CLS");

                break;
            }

        case 3:
            {
                XStack<BookItem>* SortStack = new XStack<BookItem>();
                XStack<BookItem>* TempStack = new XStack<BookItem>(*NewStack);

                NewStack->worseSellers(SortStack, TempStack);

                NewStack->displaySortedBooks(SortStack, 5);

                delete SortStack;
                delete TempStack;

                system("PAUSE");

                system("CLS");

                break;
            }

        case 4:
            {
                XStack<BookItem>* SortStack = new XStack<BookItem>();
                XStack<BookItem>* TempStack = new XStack<BookItem>(*NewStack);

                NewStack->RecentBooks(SortStack, TempStack);

                NewStack->displaySortedBooks(SortStack, 10);

                delete SortStack;
                delete TempStack;

                system("PAUSE");

                system("CLS");

                break;
            }

        case 5:
            {
                string Word;
                cout << "\nEnter keyword to search for Book(s): ";
                cin >> Word;

                NewStack->keywordSearch(Word);

                system("PAUSE");

                system("CLS");

                break;
            }

        case 6:
            {
                int unique_author;
                cout << "\nHow many top unique authors do you want to see? Enter: ";
                cin >> unique_author;

                XStack<BookItem>* UniqueStack = new XStack<BookItem>();
                XStack<BookItem>* UniqueSortedStack = new XStack<BookItem>();
                XStack<BookItem>* TempStack = new XStack<BookItem>(*NewStack);


                NewStack->uniqueAuthors(UniqueStack, TempStack);

                NewStack->topSellers(UniqueSortedStack, UniqueStack);

                NewStack->displaySortedBooks(UniqueSortedStack, unique_author);

                delete UniqueSortedStack;
                delete UniqueStack;
                delete TempStack;

                system("PAUSE");

                system("CLS");

                break;
            }

        }


    } while (option_book >= 1 && option_book <= 6);

    return;
}

int main()
{
    XStack<BookItem>* NewStack = new XStack<BookItem>();

    readData("db_small.txt", NewStack);

    int option;

    do
    {
        cout << "\nOptions:\n"
             << "\n1: Play with Stack\n"
             << "2: View Book Statistics or search for a particular book\n"
             << "\nEnter any other number for exit\n"
             << "\nEnter your option number: ";
        cin >> option;

        switch(option)
        {

        case 1 : system("CLS");
                 PlayStack();
                 break;

        case 2: system("CLS");
                BookStatistics();
                break;
        }

       system("CLS");

    } while(option >= 1 && option <= 2);

    return 0;
}

#endif // MAIN_CPP
