//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main (int argc, char* argv[])
{
    // check arguments
    if (argc < 3) {
        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return -1;
    }
    int option;
    int hashTableSize = atoi(argv[2]);
    HashOpenAddressing *hash1 = new HashOpenAddressing(hashTableSize);
    HashChaining* hash2 = new HashChaining(hashTableSize);
    do {
        // print the menu
        cout << "=======Main Menu=======" << endl;
        cout << "1. Populate hash tables" << endl;
        cout << "2. Search for a course" << endl;
        cout << "3. Search for a professor" << endl;
        cout << "4. Display all courses" << endl;
        cout << "5. Exit" << endl;

        // get option from user
        cout << "\nEnter an option: ";
        cin >> option;

        if (option == 1) {
            // handle for option the user select load hash tables from input file
            cout << "\n[OPEN ADDRESSING] Hash table populated" << endl;
            cout << "--------------------------------------" << endl;
            hash1->bulkInsert(argv[1]);
            cout << endl;
            cout << "\n[CHAINING] Hash table populated" << endl;
            cout << "--------------------------------------" << endl;
            hash2->bulkInsert(argv[1]);
            cout << endl;
        }
        else if (option == 2) {
            // handle for option the user select search for a course
            // asking user enter course year, course number and professor id to searching
            cout << endl;
            int year, courseNum;
            string profid;
            cout << "Enter the course year (e.g. 2021):" << endl;
            cin >> year;
            cout << "Enter a course number (e.g. 2270):" << endl;
            cin >> courseNum;
            cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
            cin >> profid;
            
            // using open addressing to search
            cout << "\n[OPEN ADDRESSING] Search for a course" << endl;
            cout << "--------------------------------------" << endl;
            hash1->search(year, courseNum, profid);
            cout << endl;

            // using chaining to search
            cout << "\n[CHAINING] Search for a course" << endl;
            cout << "--------------------------------------" << endl;
            hash2->search(year, courseNum, profid);
            cout << endl;
        }
        else if (option == 3) {
            // handle for option the user select search for a professor
            // asking user enter professor id to searching
            string profid;
            cout << "Enter a Professor's ID (e.g. nscollan0):" << endl;
            cin >> profid;

            // using open addressing to search
            cout << "\n[OPEN ADDRESSING] Search for a professor" << endl;
            cout << "--------------------------------------" << endl;
            hash1->profDb.publicSearchProfessor(profid);
            cout << endl;

            // using chaining to search
            cout << "\n[CHAINING] Search for a professor" << endl;
            cout << "--------------------------------------" << endl;
            hash2->profDb.publicSearchProfessor(profid);
            cout << endl;
        }
        else if (option == 4) {
            // handle for option the user select display all courses
            // asking the type of hash map user want to display courses for
            string type;
            cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)?" << endl;
            cin >> type;
            if (type == "O") {
                // user select display courses for open addressing
                cout << "\n[OPEN ADDRESSING] displayAllCourses()" << endl;
                cout << "--------------------------------------" << endl;
                hash1->displayAllCourses();
            }
            else if (type == "C") {
                // user select display courses for chaining
                cout << "\n[CHAINING] displayAllCourses()" << endl;
                cout << "--------------------------------------" << endl;
                hash2->displayAllCourses();
            }
            cout << endl;
        }
        else if (option == 5) {
            // user select exit
            // free memory before exit
            delete hash1;
            delete hash2;
        }
        else {
            // user select invalid option
            cout << "Invalid option." << endl;
        }
    } while (option != 5);

    return 0;
}