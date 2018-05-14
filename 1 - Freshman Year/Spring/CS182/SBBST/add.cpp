#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
add.cpp
This file contains the public and private add methods for the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/


//public add
template bool MySBBST<int, int, intintCompare, intintCompare>::add(int);
template bool MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::add(student);
/**
	add(Elem e)
	A public method that takes an element, then calls a private method which recursively finds the correct place to add said element in a node.

	Input: Elem e: the element that is used to make a new node, which is then sent to the private recursive add method.

	Returns: A boolean, returning true if the element was successfully added to the tree, false if otherwise.
*/
template <class Elem, class Key, class EEComp, class KEComp>
bool MySBBST<Elem, Key, EEComp, KEComp>::add(Elem e)
{
	if (!(EEComp::eq(e, zero))) //if given element does not match the zero
	{
		if (root == NULL) //if root does not exist, set root to given elem
		{
			root = new MySBBSTNode(e);
			problemCheck();
			return true;
		}
		else //call recursive add
		{
			bool result = add(root, e);
			problemCheck();
			return result;
		}
	}

	return false;
}



//private add
template bool MySBBST<int, int, intintCompare, intintCompare>::add(MySBBSTNode *&, int);
template bool MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::add(MySBBSTNode *&, student);
/**
	add(MySBBSTNode *&, Elem e)
	A private method that recursively tries to add a node with the given element to the tree.
	It checks node's element and compares it to Elem e, then tries to add it to its left or right child if it can.
	If not, it recursively calls this method with the left or right child.

	Input: MySBBSTNode *&node: The node the method is currently looking at.
	Elem e: The element we are trying to add.

	Return: A boolean, which tells us if we have successfully added our Elem e to the tree as a node.
*/
template <class Elem, class Key, class EEComp, class KEComp>
bool MySBBST<Elem, Key, EEComp, KEComp>::add(MySBBSTNode *&node, Elem e)
{
	if (EEComp::lt(e, node->data)) //if our e is less than current node e, go left
	{
		if (node->leftChild == NULL)
		{
			node->leftChild = new MySBBSTNode(e);
			return true;
		}
		else
			return add(node->leftChild, e);
	}
	else //otherwise, go right
	{
		if (node->rightChild == NULL)
		{
			node->rightChild = new MySBBSTNode(e);
			return true;
		}
		else
			return add(node->rightChild, e);
	}
}

