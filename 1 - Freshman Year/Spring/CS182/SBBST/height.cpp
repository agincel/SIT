#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains the non-recursive and recursive calls for height, for the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/



//private height()
template int MySBBST<int, int, intintCompare, intintCompare>::height();
template int MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::height();
/*
	height()
	The unrecursive call for height, which calls the recursive call for height
	starting with the root.

	No input.

	Return: An int, which is the height of the root.
*/
template <class Elem, class Key, class EEComp, class KEComp>
int MySBBST<Elem, Key, EEComp, KEComp>::height()
{
	return height(root);
}



//private height(MySBBSTNode *)
template int MySBBST<int, int, intintCompare, intintCompare>::height(MySBBSTNode *);
template int MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::height(MySBBSTNode *);
/*
	height(MySBBSTNode *)
	The recursive call that sets the height of each node in the tree. 
	It takes the max height of the left or right branch, and sets the node's height to 1 + that.

	Input: MySBBSTNode *node: The node currently having its height defined.

	Return: An int reflecting the height of the current node.

	Outcome: Each node on the tree has an accurate height set once this recursive call is finished.
*/
template <class Elem, class Key, class EEComp, class KEComp>
int MySBBST<Elem, Key, EEComp, KEComp>::height(MySBBSTNode *node)
{
	if (node == NULL) //if you are a null your height is 0
	{
		return 0;
	}

	int leftHeight = 1 + height(node->leftChild); 
	int rightHeight = 1 + height(node->rightChild);

	if (leftHeight > rightHeight) //if there are more nodes on left than right
	{
		node->height = leftHeight;
		return leftHeight;
	}
	else
	{
		node->height = rightHeight;
		return rightHeight;
	}
}


