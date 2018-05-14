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




//public remove
template int MySBBST<int, int, intintCompare, intintCompare>::remove(int);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::remove(unsigned int);
/**
	remove(Key k)
	The public remove method; it takes a key, checks to make sure the key doesn't match the zero value of the tree,
	then calls the recursive remove function using root and the given key.

	Input: Key k: The key corresponding to the value we want to remove.

	Return: The Elem which got removed.
*/
template <class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::remove(Key k)
{
	if (!(KEComp::eq(k, zero))) //if key does not match the key corresponding to zero
	{
		Elem result = remove(root, k);
		problemCheck();
		return result;
	}

	return zero;
}



//private remove
template int MySBBST<int, int, intintCompare, intintCompare>::remove(MySBBSTNode *&, int);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::remove(MySBBSTNode *&, unsigned int);
/**
	remove(MySBBSTNode *&, Key k)
	The private recursive remove method. Sees if we have reached the node to be removed, if not, checks if we need to remove
	from the left or right.

	Input: MySBBSTNode *&node: The node currently being checked.
	Key k: The key being checked against the nodes; corresponds to the node to be deleted.

	Returns: The Elem which got removed from the tree.

	Outcome: in removing a node, it attaches it assigns one of its children to replace it, depending on the circumstances.
*/
template <class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::remove(MySBBSTNode *&node, Key k)
{
	Elem tmp;
	MySBBSTNode *deleteMe = NULL;

	if (node == NULL)
		return zero;

	if (KEComp::eq(k, node->data)) //if our key matches the key of the data of this node, it's what we're looking for
	{
		tmp = node->data;

		if (node->leftChild != NULL && node->rightChild != NULL)
			node->data = removeMin(node->rightChild); //removes largest element smaller than the current node and sets it here
		else
		{
			deleteMe = node;
			if (node->leftChild == NULL)
				node = node->rightChild;
			else
				node = node->leftChild;

			delete deleteMe;
		}

		return tmp;
	}
	else
	{
		Elem leftResult = remove(node->leftChild, k); //keep searching left first
		if (EEComp::eq(leftResult, zero)) //if you got zero on all left, check right
		{
			Elem rightResult = remove(node->rightChild, k); //if you got a result on right or you got zero all the way, doesn't matter
			return rightResult;
		}
		else
			return leftResult;

		//this only removes one thing, not all instances
		
	}
}



//private removeMin
template int MySBBST<int, int, intintCompare, intintCompare>::removeMin(MySBBSTNode *&);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::removeMin(MySBBSTNode *&);
/*
removeMin(MySBBSTNode *&)
A private recursive method that removes the leftmost node starting at the given node.

Input: MySBBSTNode *&node: The node being checked. If it isn't the leftmost node, it calls this method
with its left child.

Return: Returns the Elem of the removed node.
*/
template <class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::removeMin(MySBBSTNode *&node)
{
	Elem tmp;
	MySBBSTNode *deleteMe;
	if (node == NULL)
		return zero;

	if (node->leftChild == NULL) //if you can't go left anymore
	{
		tmp = node->data;
		deleteMe = node;
		node = node->rightChild;
		delete deleteMe;
		return tmp;
	}

	return removeMin(node->leftChild); //otherwise keep going left
}

