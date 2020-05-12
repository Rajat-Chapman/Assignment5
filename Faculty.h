#ifndef _INCL_FACULTY
#define _INCL_FACULTY

#include <iostream>
#include "DoublyLinkedList.h"
#include "Person.h"

using namespace std;
//modify to use DoublyLinkedList
class Faculty : public Person
{
    public:
        string department;
        DoublyLinkedList<int> adviseeIDArray;

        Faculty();
        Faculty(int i, string n, string l, string d);
        ~Faculty();

        void print();

        void printAdvisees();

        void addAdvisee(int aid);
        void removeAdvisee(int adviseeID);

        int getMaxArraySize();

        string getDepartment();
        int getNumAdvisees();
};
#endif
