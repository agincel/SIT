#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains the isValidTree method for the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/




//public isValidTree
template bool MySBBST<int, int, intintCompare, intintCompare>::isValidTree();
template bool MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::isValidTree();
/*
	isValidTree()
	A public method that returns a boolean reflecting whether or not a tree is AVL compliant.

	No input.

	Return: A bool; true if tree is valid, false if tree is invalid.
*/
template <class Elem, class Key, class EEComp, class KEComp>
bool MySBBST<Elem, Key, EEComp, KEComp>::isValidTree()
{
	return isValidTree(root);
}



//private isValidTree
template bool MySBBST<int, int, intintCompare, intintCompare>::isValidTree(MySBBSTNode *);
template bool MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::isValidTree(MySBBSTNode *);
/*
	isValidTree()
	A private recursive method that traverses the tree and checks to make sure there are no AVL violations.

	Input: MySBBSTNode *node: The node being checked for an AVL violation.

	Return: A bool; true if node is valid, false if node is invalid.
*/
template <class Elem, class Key, class EEComp, class KEComp>
bool MySBBST<Elem, Key, EEComp, KEComp>::isValidTree(MySBBSTNode *node)
{
	if (node != NULL)
	{
		bool leftTest = isValidTree(node->leftChild);
		bool rightTest = isValidTree(node->rightChild);

		if (node->order > 1 || node->order < -1) //order is bad
			return false;
		else
			return (leftTest && rightTest);
	}

	return true;
}





