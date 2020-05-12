#include "Faculty.h"
#include <iostream>
using namespace std;

//implements functions required to hold Faculty information
Faculty::Faculty() {

}

Faculty::Faculty(int i, string n, string l, string d) {
    id = i;
    string nc = n; //copied strings to prevent scope issues
    string lc = l;
    string dc = d;
    name = nc;
    level = lc;
    department = dc;
}

Faculty::~Faculty() {

}

void Faculty::print() {
    cout << "Faculty ID: " << id << " | Name: " << name << " | Level: " << level << " | Dept: " << department << "\nAdvisee IDs: " << endl;
    printAdvisees();
    cout << endl;
}

void Faculty::printAdvisees() {
    adviseeIDArray.printList();
}

void Faculty::addAdvisee(int adviseeID) {
    adviseeIDArray.insertBack(adviseeID);
}

void Faculty::removeAdvisee(int adviseeID) {
    adviseeIDArray.removeAt(adviseeID);
}

string Faculty::getDepartment() {
    return department;
}
