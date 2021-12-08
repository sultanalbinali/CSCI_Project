//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

/**
* Contructor for HashOpenAddressing class
*
* @param size - size of hash table
*/
HashOpenAddressing::HashOpenAddressing(int size)
{
	hashTableSize = size;
	hashTable = new Course * [size];
	for (int i = 0; i < hashTableSize; i++) {
		hashTable[i] = nullptr;
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
int HashOpenAddressing::split(string str, char delimiter, string arr[], int size) {
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
* isFull - This function check if hash table is full or not
*
* @return true - when hash table is full and false - when hash table not full
*/
bool HashOpenAddressing::isFull()
{
	for (int i = 0; i < hashTableSize; i++) {
		if (hashTable[i] == nullptr)
			return false;
	}
	return true;
}

/**
* split - This function finding a course by course year, number and professor id.
* We keep update the search operation and collisions during finding a course.
* We do that for save the number of search operation, we just need finding once time
* and keep the index of bucket where the course should be insert in case cannot found
* course in hash table
*
* @param courseYear - year of course
* @param courseNumber - number of course
* @param profId - professor id of this course
* @param searchOperation - keep update for number of search operation to find the course in hash table
* @param collisions - keep update for number of collisions happened to find the course in hash table
* @return index of bucket where this course should be insert in case not found course in hash table
* If can find course in hash table, then return -1. In case cannot found the course and hash table is full then return -2.
*/
int HashOpenAddressing::findCourse(int courseYear, int courseNumber, string profId, int& searchOperation, int& collisions)
{
	// we need to keep the list of buckets index has been searching
	// then we will stop when detect one bucket duplicated
	vector<int> visitedBuckets;
	// calculate the bucket index
	int index = hash(courseNumber);
	int i = 0;
	bool stop = false;
	// initial number of search operation
	Course* result = nullptr;
	while (!stop) {
		searchOperation++;
		// if this bucket is empty, mean that this element not existed in hash table
		if (hashTable[index] == nullptr) {
			// then stop search and return the index of bucket where the course should be there
			return index;
		}
		// if found this course, then stop search
		if (hashTable[index]->year == courseYear && hashTable[index]->courseNum == courseNumber && hashTable[index]->prof != nullptr && hashTable[index]->prof->profId == profId) {
			result = hashTable[index];
			return -1;
		}
		// marked that this bucket index has been visited
		visitedBuckets.push_back(index);
		// Calculate the new index in case has collisions in this index
		i++;
		index = (index + i * i) % hashTableSize;
		collisions++;
		// now check that this new index not visited yet
		for (int i = 0; i < visitedBuckets.size(); i++) {
			// if this new index has been visited, then stop searching
			if (index == visitedBuckets[i]) {
				stop = true;
				break;
			}
		}
	}
	// return -2 as this hashtable full but cannot find this course
	return -2;
}

/**
* Destructor of class HashOpenAddressing, free all memory allocated for this hash map
*/
HashOpenAddressing::~HashOpenAddressing()
{
	for (int i = 0; i < hashTableSize; i++) {
		if (hashTable[i] != nullptr)
			delete hashTable[i];
	}
	delete[] hashTable;
}

/**
* hash - This function calculates the hash of a key
*
* @param courseNumber - the number of course
* @return int
*/
int HashOpenAddressing::hash(int courseNumber)
{
	return courseNumber % hashTableSize;
}

/**
* bulkInsert - This function insert list of course from file input
*
* @param filename - name of file input (csv) to read and insert course into hash table
*/
void HashOpenAddressing::bulkInsert(string filename)
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
			int subCollisions = 0;
			int index = findCourse(year, courseNumber, profid, searchOperation, subCollisions);
			// if this course not existed in hash table, then add it into hash table
			if (index > -1 && !isFull()) {
				Course* newCourse = new Course(year, arr[1], courseNumber, arr[3], p);
				p->coursesTaught.push_back(newCourse);
				// add course into hash map
				hashTable[index] = newCourse;
				collisions += subCollisions;
			}
		}
	}
	in1.close();
	// print the summary information
	cout << "Collisions using open addressing: " << collisions << endl;
	cout << "Search operations using open addressing: " << searchOperation << endl;
}

/**
* search - This function searching a course by course year, number and professor id
*
* @param courseYear - year of course
* @param courseNumber - number of course
* @param profId - professor id of this course
*/
void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
	// we need to keep the list of buckets index has been searching
	// then we will stop when detect one bucket duplicated
	vector<int> visitedBuckets;
	// calculate the bucket index
	int index = hash(courseNumber);
	int i = 0;
	bool stop = false;
	// initial number of search operation
	int searchOperation = 0;
	Course* result = nullptr;
	while (!stop) {
		searchOperation++;
		// if this bucket is empty, mean that this element not existed in hash table
		if (hashTable[index] == nullptr) {
			// then stop search
			break;
		}
		// if found this course, then stop search
		if (hashTable[index]->year == courseYear && hashTable[index]->courseNum == courseNumber && hashTable[index]->prof != nullptr && hashTable[index]->prof->profId == profId) {
			result = hashTable[index];
			break;
		}
		// marked that this bucket index has been visited
		visitedBuckets.push_back(index);
		// Calculate the new index in case has collisions in this index
		i++;
		index = (index + i * i) % hashTableSize;
		// now check that this new index not visited yet
		for (int i = 0; i < visitedBuckets.size(); i++) {
			// if this new index has been visited, then stop searching
			if (index == visitedBuckets[i]) {
				stop = true;
				break;
			}
		}
	}
	// print the number of operation using to search for this course
	cout << "Search operations using open addressing: " << searchOperation << endl;
	// call the displayCourseInfo() to print this course
	displayCourseInfo(result);
}

/**
* displayAllCourses - This function display all courses in hash table
*/
void HashOpenAddressing::displayAllCourses()
{
	// go each bucket, if bucket not empty then print it
	for (int i = 0; i < hashTableSize; i++) {
		if (hashTable[i] != nullptr) {
			cout << hashTable[i]->year << " " << hashTable[i]->courseName << " " << hashTable[i]->courseNum << " " << hashTable[i]->prof->profName << endl;
		}
	}
}

/**
* displayCourseInfo - This function display information of course
*
* @param c - course we want to display information
*/
void HashOpenAddressing::displayCourseInfo(Course* c)
{
	// if course is empty, then print message that wasn't found this course
	if (c == nullptr) {
		cout << "Course not found." << endl;
	}
	else {
		// in case found this course, then print the  information of it
		cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
	}
}