#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains the problem checking and solving methods for the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/


//private rotate left
template void MySBBST<int, int, intintCompare, intintCompare>::rotateLeft(MySBBSTNode *&);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::rotateLeft(MySBBSTNode *&);
/*
	rotateLeft(MySBBSTNode *&)
	Private method that rotates a given node left. 
	
	Input: MySBBSTNode *&node: The node being rotated.

	No return.
	Outcome: Right child will replace current node, and current node will become left child of that replacement.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::rotateLeft(MySBBSTNode *&node)
{
	if (node != NULL)
	{
		MySBBSTNode *tmp = node->rightChild;
		node->rightChild = tmp->leftChild;
		tmp->leftChild = node;
		node = tmp;

		order();
	}
}



//private rotate right
template void MySBBST<int, int, intintCompare, intintCompare>::rotateRight(MySBBSTNode *&);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::rotateRight(MySBBSTNode *&);
/*
	rotateRight(MySBBSTNode *&)
	Private method that rotates a given node right.

	Input: MySBBSTNode *&node: The node being rotated.

	No return.
	Outcome: Left child will replace current node, and current node will become right child of that replacement.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::rotateRight(MySBBSTNode *&node)
{
	if (node != NULL)
	{
		MySBBSTNode *tmp = node->leftChild;
		node->leftChild = tmp->rightChild;
		tmp->rightChild = node;
		node = tmp;

		order();
	}
}


//private problemCheck()
template void MySBBST<int, int, intintCompare, intintCompare>::problemCheck();
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::problemCheck();
/*
	problemCheck()
	Non-recursive method that orders tree then checks for any AVL violations.

	No input.

	No return.
	Outcome: Tree will be AVL compliant after this method terminates.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::problemCheck()
{
	order();
	problemCheck(root);
}

//private recursive problemCheck
template void MySBBST<int, int, intintCompare, intintCompare>::problemCheck(MySBBSTNode *&);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::problemCheck(MySBBSTNode *&);
/*
	problemCheck(MySBBSTNode *&)
	Recursive method that handles AVL violations going down the tree.
	Checks for LL, LR, RR, and RL problems and handles them accordingly.

	Input: MySBBSTNode *&node: The node currently being checked for errors.

	No return.
	Outcome: Tree will be AVL compliant after this recursive method is finished.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::problemCheck(MySBBSTNode *&node)
{
	if (node != NULL)
	{
		order();
		if (node->order < -1) //Left Left or Left Right problem
		{
			if (node->leftChild->order < 0) //left left problem
			{
				rotateRight(node);
			}
			else if (node->leftChild->order >= 0) //left right problem
			{
				rotateLeft(node->leftChild);
				rotateRight(node);
			}

			problemCheck(node);
		}
		else if (node->order > 1) //Right Right or Right Left)
		{
			if (node->rightChild->order < 0) //right left problem
			{
				rotateRight(node->rightChild);
				rotateLeft(node);
			}
			else if (node->rightChild->order >= 0) //right right
			{
				rotateLeft(node);
			}

			problemCheck(node);
		}
		else
		{
			problemCheck(node->leftChild);
			problemCheck(node->rightChild);
		}

	}

}
