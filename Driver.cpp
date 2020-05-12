
#include "Faculty.h"
#include "Student.h"
#include "BST.h"
#include <iostream>
#include <fstream>
using namespace std;

BST<Faculty> facultyTree;
BST<Student> studentTree;

void fillTrees() {
    //ONLY FOR TESTING PURPOSES
    cout << "Starting creating faculty objects" << endl;
    Faculty aone(111, "paul", "teaching prof", "sociology");
    Faculty bone(222, "steve", "assistant prof", "economics");
    Faculty done(333, "lily", "senior prof", "finance");
    Faculty eone(444, "joey", "genius prof", "accounting");
    Faculty fone(555, "miranda", "teaching prof", "chemistry");
    Faculty gone(666, "adam", "senior prof", "physics");

    cout << "Starting creating student objects" << endl;
    Student hone(777, "brie", "junior", 3.2, "economics", 111);
    Student ione(888, "allie", "senior", 2.1, "physics", 111);
    Student jone(999, "john", "freshman", 4.0, "accounting", 444);
    Student kone(101, "stan", "sophmore", 2.7, "finance", 333);
    Student lone(102, "eve", "junior", 3.6, "biology", 666);
    Student mone(103, "lee", "sophmore", 2.2, "accounting", 222);

    cout << "Starting creating/inserting faculty nodes" << endl;
    //create tree nodes and add to trees
    //TreeNode<Faculty> aoneNode(&aone, aone.id);
    facultyTree.insert(aone);
    //TreeNode<Faculty> boneNode(&bone, bone.id);
    facultyTree.insert(bone);
    //TreeNode<Faculty> doneNode(&done, done.id);
    facultyTree.insert(done);
    //TreeNode<Faculty> eoneNode(&eone, eone.id);
    facultyTree.insert(eone);
    //TreeNode<Faculty> foneNode(&fone, fone.id);
    facultyTree.insert(fone);
    //TreeNode<Faculty> goneNode(&gone, gone.id);
    facultyTree.insert(gone);

    cout << "Starting creating/inserting student nodes" << endl;
    //create tree nodes and add to trees
    //TreeNode<Student> honeNode(&hone, hone.id);
    studentTree.insert(hone);
    facultyTree.search(hone.advisorID)->addAdvisee(hone.id);

    //TreeNode<Student> ioneNode(&ione, ione.id);
    studentTree.insert(ione);
    facultyTree.search(ione.advisorID)->addAdvisee(ione.id);

    //TreeNode<Student> joneNode(&jone, jone.id);
    studentTree.insert(jone);
    facultyTree.search(jone.advisorID)->addAdvisee(jone.id);

    //TreeNode<Student> koneNode(&kone, kone.id);
    studentTree.insert(kone);
    facultyTree.search(kone.advisorID)->addAdvisee(kone.id);

    //TreeNode<Student> loneNode(&lone, lone.id);
    studentTree.insert(lone);
    facultyTree.search(lone.advisorID)->addAdvisee(lone.id);

    //TreeNode<Student> moneNode(&mone, mone.id);
    studentTree.insert(mone);
    facultyTree.search(mone.advisorID)->addAdvisee(mone.id);

}

void printTrees() {
    facultyTree.printTree();
    studentTree.printTree();
}

//Command 1: Print all students and their information (sorted by ascending id #)
void printStudentTable() {
    studentTree.printTree();
}

//Command 2: Print all faculty and their information (sorted by ascending id #)
void printFacultyTable() {
    facultyTree.printTree();
}

//Command 3: Find and display student information given the students id
void findStudent(int sid) {
    Student* stemp = studentTree.search(sid);
    if(stemp != NULL) stemp->print();
    else cout << "Student not found" << endl;
}

//Command 4: Find and display faculty information given the faculty id
void findFaculty(int fid) {
    Faculty* stemp = facultyTree.search(fid);
    if(stemp != NULL) stemp->print();
    else cout << "Faculty not found" << endl;
}

//Command 5: Given a student’s id, print the name and info of their faculty advisor
void printAdvisorInfo(int sid) {
    Student* stemp = studentTree.search(sid);
    if(stemp != NULL)
        facultyTree.search(stemp->getAdvisorID())->print();
    else
        cout << "Student not found" << endl;
}

//Command 6: Given a faculty id, print ALL the names and info of his/her advisees
void findAdvisees(int fid) {
    Faculty* stemp = facultyTree.search(fid);
    if(stemp != NULL) stemp->printAdvisees();
    else cout << "Faculty not found" << endl;
}

//Command 7: Add a new student
void addStudent(int s, string n, string l, double g, string m, int a) {

    Faculty* ftemp = facultyTree.search(a);
    if(ftemp != NULL) {
        Student stemp(s, n, l, g, m, a);
        studentTree.insert(stemp);
        facultyTree.search(stemp.advisorID)->addAdvisee(stemp.id);
    } else {
        cout << "Faculty not found" << endl;
    }
}

//Command 8: Delete a student given the id
//Also deletes student as advisee from faculty table to maintin integrity
void deleteStudent(int sid) {
    Student* stemp = studentTree.search(sid);
    if(stemp != NULL) {
        int fid = stemp->advisorID;
        Faculty* ftemp = facultyTree.search(fid);
        ftemp->removeAdvisee(sid);
        studentTree.deleteNode(sid);
    } else {
        cout << "Student not found" << endl;
    }
}

//Command 9: Add a new faculty member
void addFaculty(int s, string n, string l, string m) {
    Faculty ftemp(s, n, l, m);
    facultyTree.insert(ftemp);
}

//Command 10: Delete a faculty member given the id
void deleteFaculty(int fid) {
    Faculty* ftemp = facultyTree.search(fid);
    int stemp;
    if(ftemp != NULL) {
        DoublyLinkedList<int> adList = ftemp->adviseeIDArray;
        ListNode<int> *current = adList.front;
        if (!adList.isEmpty()) {
            while (true) {
                stemp = current->data;
                studentTree.search(stemp)->setAdvisorID(-1);
                if (current->next == NULL) {
                    break;
                }
                current = current->next;
            }
        }
        facultyTree.deleteNode(fid);
    } else {
        cout << "Faculty member not found" << endl;
    }
}

//Command 11: Change a student’s advisor given the student id and the new faculty id
void changeAdvisor(int sid, int fid) {
    //remove advisee from old faculty, add to new advisee list
    //set advisor id to new advisor id
    Student* stemp = studentTree.search(sid);
    if(stemp != NULL) {
        int tempid = stemp->getAdvisorID();
        Faculty* tempf = facultyTree.search(tempid);
        if(tempf != NULL) {
            tempf->removeAdvisee(sid);
        }

        Faculty* tempg = facultyTree.search(fid);
        if(tempg != NULL) {
            studentTree.search(sid)->setAdvisorID(fid);
            facultyTree.search(fid)->addAdvisee(sid);
        } else {
            cout << "Faculty not found" << endl;
        }
    } else {
        cout << "Student not found" << endl;
    }
}

//Command 12: Remove an advisee from a faculty member given the ids
void deleteAdvisee(int fid, int sid) {
    //given fid=222 and sid=103, remove from advisee list
    Faculty* tempf2 = facultyTree.search(fid);
    if(tempf2 != NULL) {
        tempf2->removeAdvisee(sid);
        //must be removed from student too
        Student* stemp = studentTree.search(sid);
        if(stemp != NULL)
            stemp->setAdvisorID(-1);
        else
            cout << "Student not found" << endl;
    } else {
        cout << "Faculty not found" << endl;
    }
}

void displayOptions() {
    cout << "0: Exit Program" << endl;
    cout << "1: Print all students and their information" << endl;
    cout << "2: Print all faculty and their information" << endl;
    cout << "3: Find and display student information given the students id" << endl;
    cout << "4: Find and display faculty information given the faculty id" << endl;
    cout << "5: Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6: Given a faculty id, print ALL the names and info of his/her advisees" << endl;
    cout << "7: Add a new student" << endl;
    cout << "8: Delete a student given the id" << endl;
    cout << "9: Add a new faculty member" << endl;
    cout << "10: Delete a faculty member given the id" << endl;
    cout << "11: Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "12: Remove an advisee from a faculty member given the ids" << endl;
}

int main (int argc, char** argv) {

    //FOR TESTING
    //fillTrees();

    //USER INPUT SECTION
    //vars for storing user input
    int in_option;
    int sid_option;
    int fid_option;
    string name_option;
    string level_option;
    double gpa_option;
    string major_option;
    while(true) {
        cout << "Which command would you like to run?: " << endl;
        displayOptions();
        cin >> in_option;
        switch(in_option) {
            case 0:
            return 0; //end program
            break;

            case 1:
            printStudentTable();
            cout << "-------------" << endl;
            cout << "Done command 1" << endl;
            cout << "-------------" << endl;
            break;

            case 2:
            printFacultyTable();
            cout << "-------------" << endl;
            cout << "Done command 2" << endl;
            cout << "-------------" << endl;
            break;

            case 3:
            cout << "Enter a Student ID: ";
            cin >> sid_option;
            findStudent(sid_option);
            cout << "-------------" << endl;
            cout << "Done command 3" << endl;
            cout << "-------------" << endl;
            break;

            case 4:
            cout << "Enter a Faculty ID: ";
            cin >> fid_option;
            findFaculty(fid_option);
            cout << "-------------" << endl;
            cout << "Done command 4" << endl;
            cout << "-------------" << endl;
            break;

            case 5:
            cout << "Enter a Student ID: ";
            cin >> sid_option;
            printAdvisorInfo(sid_option);
            cout << "-------------" << endl;
            cout << "Done command 5" << endl;
            cout << "-------------" << endl;
            break;

            case 6:
            cout << "Enter a Faculty ID: ";
            cin >> fid_option;
            findAdvisees(fid_option);
            cout << "-------------" << endl;
            cout << "Done command 6" << endl;
            cout << "-------------" << endl;
            break;

            case 7:
            cout << "Enter a Student ID: ";
            cin >> sid_option;
            cout << "Enter a Name: ";
            cin >> name_option;
            cout << "Enter a Level: ";
            cin >> level_option;
            cout << "Enter a GPA: ";
            cin >> gpa_option;
            cout << "Enter a Major: ";
            cin >> major_option;
            cout << "Enter an Advisor ID: ";
            cin >> fid_option;
            addStudent(sid_option, name_option, level_option, gpa_option, major_option, fid_option);
            cout << "-------------" << endl;
            cout << "Done command 7" << endl;
            cout << "-------------" << endl;
            break;

            case 8:
            cout << "Enter a Student ID: ";
            cin >> sid_option;
            deleteStudent(sid_option);
            cout << "-------------" << endl;
            cout << "Done command 8" << endl;
            cout << "-------------" << endl;
            break;

            case 9:
            cout << "Enter a Faculty ID: ";
            cin >> sid_option;
            cout << "Enter a Name: ";
            cin >> name_option;
            cout << "Enter a Level: ";
            cin >> level_option;
            cout << "Enter a Department: ";
            cin >> major_option;
            addFaculty(sid_option, name_option, level_option, major_option);
            cout << "-------------" << endl;
            cout << "Done command 9" << endl;
            cout << "-------------" << endl;
            break;

            case 10:
            cout << "Enter a Faculty ID: ";
            cin >> fid_option;
            deleteFaculty(fid_option);
            cout << "-------------" << endl;
            cout << "Done command 10" << endl;
            cout << "-------------" << endl;
            break;

            case 11:
            cout << "Enter a Student ID: ";
            cin >> sid_option;
            cout << "Enter a Faculty ID: ";
            cin >> fid_option;
            changeAdvisor(sid_option, fid_option);
            cout << "-------------" << endl;
            cout << "Done command 11" << endl;
            cout << "-------------" << endl;
            break;

            case 12:
            cout << "Enter a Faculty ID: ";
            cin >> fid_option;
            cout << "Enter a Student ID: ";
            cin >> sid_option;
            deleteAdvisee(fid_option, sid_option);
            cout << "-------------" << endl;
            cout << "Done command 12" << endl;
            cout << "-------------" << endl;
            break;

            default:
            cout << "Please try again, did not understand command!" << endl;
            break;
        }

    }

    return 0;
}
