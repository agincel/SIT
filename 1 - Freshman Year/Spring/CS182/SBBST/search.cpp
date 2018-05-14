#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains methods used to search through the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/



//public search
template int MySBBST<int, int, intintCompare, intintCompare>::search(int);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::search(unsigned int);
/*
	search(Key k)
	The public call for search. Checks to see if Key matches the key for the zero value,
	and if it doesn't, it calls the private Search.

	Input: Key k: The key being searched for.

	Return: The Elem, if it gets found. Otherwise returns zero value.
*/
template <class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::search(Key k)
{
	if (!(KEComp::eq(k, zero))) //if the given key doesn't match the zero
	{
		return search(root, k);
	}

	return zero;
}



//private search
template int MySBBST<int, int, intintCompare, intintCompare>::search(MySBBSTNode *, int);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::search(MySBBSTNode *, unsigned int);
/*
	search(MySBBSTNode *, Key k)
	Private call for search. Checks to see if current node matches key,
	otherwise compares keys and recursively calls with either left or right child.

	Input: MySBBSTNode *node: The node currently being checked.
		   Key k: The key being compared against the node.

	Return: The Elem, if it gets found. Otherwise returns zero.	
*/
template <class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::search(MySBBSTNode *node, Key k)
{
	if (node == NULL) //key not found, return zero
		return zero;

	if (KEComp::eq(k, node->data)) //if we found the node
		return node->data;

	if (KEComp::lt(k, node->data)) //if we need to move left
		return search(node->leftChild, k);
	else //otherwise move right
		return search(node->rightChild, k);
}


