//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.h
//-----------------------------------------------------------------------------

#ifndef HASHOPENADDRESSING_H
#define HASHOPENADDRESSING_H

#include "util.h"
#include "ProfBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class HashOpenAddressing
{
	public:
		/**
		* Contructor for HashOpenAddressing class
		*
		* @param size - size of hash table
		*/
		HashOpenAddressing(int size);

		/**
		* Destructor of class HashOpenAddressing, free all memory allocated for this hash map
		*/
		~HashOpenAddressing();
		
		/**
		* search - This function searching a course by course year, number and professor id
		*
		* @param courseYear - year of course
		* @param courseNumber - number of course
		* @param profId - professor id of this course
		*/
        void search(int courseYear, int courseNumber, string profId);

		/**
		* bulkInsert - This function insert list of course from file input
		*
		* @param filename - name of file input (csv) to read and insert course into hash table
		*/
		void bulkInsert(string filename);
		
		/**
		* displayAllCourses - This function display all courses in hash table
		*/
        void displayAllCourses();

		/**
		* displayCourseInfo - This function display information of course
		*
		* @param c - course we want to display information
		*/
		void displayCourseInfo(Course* c);
		
		/**
		* hash - This function calculates the hash of a key
		*
		* @param courseNumber - the number of course
		* @return int
		*/
		int hash(int courseNumber);

		ProfBST profDb;
		
	private:

		/**
		* split - This function split an string by delimiter
		*
		* @param str - string need to split
		* @param delimiter - char need to use for split
		* @param arr - array of string contain subtring result
		* @param size - size of array
		* @return int - number of substring in this split
		*/
		int split(string str, char delimiter, string arr[], int size);

		/**
		* isFull - This function check if hash table is full or not
		*
		* @return true - when hash table is full and false - when hash table not full
		*/
		bool isFull();

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
		int findCourse(int courseYear, int courseNumber, string profId, int& searchOperation, int& collisions);

		int hashTableSize;
		Course **hashTable;
};

#endif