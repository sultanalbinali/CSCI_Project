//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.h
//-----------------------------------------------------------------------------

#ifndef HASHCHAINING_H
#define HASHCHAINING_H

#include "ProfBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class HashChaining
{
	public:
		/**
		* Contructor for HashChaining class
		*
		* @param size - size of hash table
		*/
		HashChaining(int size);

		/**
		* Destructor of class HashChaining, free all memory allocated for this hash map
		*/
		~HashChaining();
		
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

		int hashTableSize;
		Course **hashTable;
};

#endif