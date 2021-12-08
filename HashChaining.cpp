//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"
#include <fstream>

using namespace std;

/**
* Contructor for HashChaining class
*
* @param size - size of hash table
*/
HashChaining::HashChaining(int size)
{
	hashTableSize = size;
	hashTable = new Course * [size];
	for (int i = 0; i < hashTableSize; i++) {
		hashTable[i] = NULL;
	}
}


/**
* split - This function split an string by delimiter
*
* @param str - string need to split
* @param delimiter - char need to use for split
* @param arr - array of string contain subtring result
* @param size - size of array
* @return int - number of substring in this split
*/
int HashChaining::split(string str, char delimiter, string arr[], int size) {
	int index = 0;
	arr[0] = "";
	for (int i = 0; i < str.length() && index < size; i++) {
		if (str.at(i) == delimiter) {
			index++;
			arr[index] = "";
		}
		else {
			arr[index].push_back(str.at(i));
		}
	}
	return index + 1;
}

/**
* Destructor of class HashChaining, free all memory allocated for this hash map
*/
HashChaining::~HashChaining()
{
	for (int i = 0; i < hashTableSize; i++) {
		while (hashTable[i] != NULL) {
			Course* currentNode = hashTable[i];
			hashTable[i] = hashTable[i]->next;
			if (hashTable[i] != NULL) {
				hashTable[i]->previous = NULL;
			}
			currentNode->next = NULL;
			delete currentNode;
		}
	}
	delete[] hashTable;
}

/**
* hash - This function calculates the hash of a key
*
* @param courseNumber - the number of course
* @return int
*/
int HashChaining::hash(int courseNumber)
{
	return courseNumber % hashTableSize;
}

/**
* bulkInsert - This function insert list of course from file input
*
* @param filename - name of file input (csv) to read and insert course into hash table
*/
void HashChaining::bulkInsert(string filename)
{
	ifstream in1;
	in1.open(filename); // Open input file
	// if cannot open file input then stop
	if (in1.fail())
	{
		return;
	}
	// reading each line from input file
	string line;
	// initial number of collisions and search operation
	int collisions = 0;
	int searchOperation = 0;
	// read header line
	getline(in1, line);
	// then begin read from second line for data
	while (getline(in1, line))
	{
		// checking if line just read is not empty to processing
		if (line != "") {
			string arr[7]; // Declare an array that will store strings from line
			int num = split(line, ',', arr, 7); // Split the line by commas
			// find professor
			Professor* p = profDb.searchProfessor(arr[4]);
			// if this professor not in database, then add it to database
			if (p == nullptr) {
				string name = arr[5] + " " + arr[6];
				profDb.addProfessor(arr[4], name);
				p = profDb.searchProfessor(arr[4]);
			}
			// search this course in hash table first
			int year = stoi(arr[0]);
			int courseNumber = stoi(arr[2]);
			string profid = arr[4];
			int index = hash(courseNumber);
			Course* currentNode = hashTable[index];
			Course* parentNode = NULL;
			bool isExisted = false;
			int subCollisions = 0;
			searchOperation++;
			while (currentNode != NULL) {
				subCollisions++;
				searchOperation++;
				if (currentNode->year == year && currentNode->courseNum == courseNumber && currentNode->prof->profId == arr[4]) {
					isExisted = true;
					break;
				}
				parentNode = currentNode;
				currentNode = currentNode->next;
			}
			if (!isExisted) {
				// if this course not existed in hash table, then add it into hash table
				collisions += subCollisions;
				Course* newCourse = new Course(year, arr[1], courseNumber, arr[3], p);
				p->coursesTaught.push_back(newCourse);
				if (hashTable[index] == NULL)
					hashTable[index] = newCourse;
				else {
					parentNode->next = newCourse;
					newCourse->previous = parentNode;
				}
			}
		}
	}
	in1.close();
	// print the summary information
	cout << "Collisions using chaining: " << collisions << endl;
	cout << "Search operations using chaining: " << searchOperation << endl;
}

/**
* search - This function searching a course by course year, number and professor id
*
* @param courseYear - year of course
* @param courseNumber - number of course
* @param profId - professor id of this course
*/
void HashChaining::search(int courseYear, int courseNumber, string profId)
{
	// calculate the bucket index
	int index = courseNumber % hashTableSize;
	bool stop = false;
	// initial number of search operation
	int searchOperation = 0;
	Course* currentNode = hashTable[index];
	while (currentNode != NULL) {
		searchOperation++;
		// if found this course, then stop search
		if (currentNode->year == courseYear && currentNode->courseNum == courseNumber && currentNode->prof->profId == profId) {
			break;
		}
		// go next node to find the course
		currentNode = currentNode->next;
	}
	searchOperation++;
	// print the number of operation using to search for this course
	cout << "Search operations using chaining: " << searchOperation << endl;
	// call the displayCourseInfo() to print this course
	displayCourseInfo(currentNode);
}

/**
* displayAllCourses - This function display all courses in hash table
*/
void HashChaining::displayAllCourses()
{
	// go each bucket, if bucket not empty then print it
	for (int i = 0; i < hashTableSize; i++) {
		if (hashTable[i] != NULL) {
			Course* currentNode = hashTable[i];
			while (currentNode != NULL) {
				cout << currentNode->year << " " << currentNode->courseName << " " << currentNode->courseNum << " " << currentNode->prof->profName << endl;
				currentNode = currentNode->next;
			}
		}
	}
}

/**
* displayCourseInfo - This function display information of course
*
* @param c - course we want to display information
*/
void HashChaining::displayCourseInfo(Course* c)
{
	// if course is empty, then print message that wasn't found this course
	if (c == NULL) {
		cout << "Course not found." << endl;
	}
	else {
		// in case found this course, then print the  information of it
		cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
	}
}