//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.h
//-----------------------------------------------------------------------------

#ifndef PROFBST_H
#define PROFBST_H

#include "util.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Professor
{
	string profId;
	string profName;
	vector<Course*> coursesTaught;
	Professor *left;
	Professor *right;

	Professor() {}
	Professor(string pId, string pName) { 
		profId = pId; 
		profName = pName;
		left = nullptr; right = nullptr; 
	}
};

// Professor BST class
class ProfBST
{
    public:
		/**
		* Contructor for ProfBST class
		*/
        ProfBST();

		/**
		* Destructor for ProfBST class, free all memory allocated for tree
		*/
        ~ProfBST();

		/**
		* addProfessor - This function add new professor into tree
		*
		* @param profId - professor id
		* @param profName - professor name
		*/
        void addProfessor(string profId, string profName);

		/**
		* publicSearchProfessor - This function search a pofessor by id
		*
		* @param profId - professor id
		*/
		void publicSearchProfessor(string profId);

		/**
		* searchProfessor - This function search a pofessor by id
		*
		* @param profId - professor id
		* @return pointer to professor
		*/
        Professor *searchProfessor(string profId);

		/**
		* displayProfessorInfo - This function display information for a professor
		*
		* @param p - a pointer of professor
		*/
		void displayProfessorInfo(Professor* p);

    private:
		// add helpers here (if needed)
		/**
		* destroyTree - free memory for a tree using recursion.
		*
		* @param node - current node need to free
		*/
		void destroyTree(Professor* node);

        Professor *root;
};

#endif