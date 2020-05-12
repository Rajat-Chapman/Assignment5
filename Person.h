#ifndef _INCL_PERSON
#define _INCL_PERSON

#include <iostream>

using namespace std;

class Person {
    public:
        int id;
        string name;
        string level;

        Person();
        ~Person();

        int getID();
        void setID(int v);

        string getName();
        string getLevel();
};
#endif
