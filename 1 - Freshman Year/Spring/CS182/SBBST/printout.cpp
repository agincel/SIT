#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains the implementations for the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/


//public printout
template void MySBBST<int, int, intintCompare, intintCompare>::printout();
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::printout();
/*
	printout()
	Public call that prints out the AVL tree in order.

	No input.

	No return.
	Outcome: Couts entire tree using in order traversal.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::printout()
{
	printout(root);
	cout << endl << endl << endl;
}



//private printout
template void MySBBST<int, int, intintCompare, intintCompare>::printout(MySBBSTNode *);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::printout(MySBBSTNode *);
/*
	printout()
	Private recursive call that prints out the AVL tree in order.

	Input: MySBBSTNode *node: The node currently being printed in order.

	No return.
	Outcome: Couts entire tree using in order traversal.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::printout(MySBBSTNode *node)
{
	if (node != NULL)
	{
		cout << "(";
		printout(node->leftChild);
		cout << node->data << ":" << node->order << " ";
		printout(node->rightChild);
		cout << ")";
	}
}

