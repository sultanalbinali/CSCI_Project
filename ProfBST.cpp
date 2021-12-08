//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

/**
* Contructor for ProfBST class
*/
ProfBST::ProfBST()
{
	root = nullptr;
}

/**
* Destructor for ProfBST class, free all memory allocated for tree
*/
ProfBST::~ProfBST()
{
	destroyTree(root);
}

/**
* addProfessor - This function add new professor into tree
*
* @param profId - professor id
* @param profName - professor name
*/
void ProfBST::addProfessor(string profId, string profName)
{
	// we finding the position of new node
	Professor* currentNode = root;
	Professor* parentNode = nullptr;
	// keep track that new node is left of parent or right of parent
	bool isLeft = false;
	while (currentNode != nullptr) {
		// update parent node
		parentNode = currentNode;
		// go left if the current profid smaller than profid of node
		if (currentNode->profId > profId) {
			currentNode = currentNode->left;
			isLeft = true;
		}
		else {
			// otherwise, go right
			currentNode = currentNode->right;
			isLeft = false;
		}
	}
	// create new node
	Professor* newNode = new Professor(profId, profName);
	// if the parent is null, then tree is empty, update the root to new node
	if (parentNode == nullptr)
		root = newNode;
	else {
		// link the new node as left child
		if (isLeft) {
			parentNode->left = newNode;
		}
		else {
			// link the new node as right child
			parentNode->right = newNode;
		}
	}
}

/**
* searchProfessor - This function search a pofessor by id
*
* @param profId - professor id
* @return pointer to professor
*/
Professor* ProfBST::searchProfessor(string profId)
{
	Professor* currentNode = root;
	while (currentNode != nullptr) {
		// we found the profid in this node, then return this node
		if (currentNode->profId == profId) {
			return currentNode;
		} else if (currentNode->profId > profId) {
			// go left to find the profid
			currentNode = currentNode->left;
		}
		else {
			// otherwise, go right to find the profid
			currentNode = currentNode->right;
		}
	}
	// if cannot found this profid then return nullptr as default
	return nullptr;
}

/**
* publicSearchProfessor - This function search a pofessor by id
*
* @param profId - professor id
*/
void ProfBST::publicSearchProfessor(string profId)
{
	Professor* p = searchProfessor(profId);
	displayProfessorInfo(p);
}

/**
* displayProfessorInfo - This function display information for a professor
*
* @param p - a pointer of professor
*/
void ProfBST::displayProfessorInfo(Professor* p)
{
	// only print when professor not null
	if (p != nullptr) {
		cout << "Name: " << p->profName << endl;
		for (int i = 0; i < p->coursesTaught.size(); i++) {
			cout << "- " << p->coursesTaught[i]->courseNum << ": " << p->coursesTaught[i]->courseName << ", " << p->coursesTaught[i]->year << endl;
		}
	}
	else {
		cout << "Professor not found." << endl;
	}
}

/**
* destroyTree - free memory for a tree using recursion.
*
* @param node - current node need to free
*/
void ProfBST::destroyTree(Professor* node)
{
	// stop when this node is empty
	if (node == nullptr)
		return;
	// delete node left first
	destroyTree(node->left);
	// then delete node right
	destroyTree(node->right);
	// and final, delete parent node
	delete node;
}
