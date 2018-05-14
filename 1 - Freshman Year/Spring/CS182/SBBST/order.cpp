#include "MySBBST.hh"
#include <iostream>
#include <cstring>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains the non-recursive and recursive calls for finding the order of nodes in the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/


//public order
template void MySBBST<int, int, intintCompare, intintCompare>::order();
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::order();
/*
	order()
	The public call for setting the order of each node in the tree. First sets all heights.

	No input.
	No return.

	Outcome: All nodes have the correct order set once this is complete.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::order()
{
	height();
	order(root);
}



//private order
template void MySBBST<int, int, intintCompare, intintCompare>::order(MySBBSTNode *);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::order(MySBBSTNode *);
/*
	order(MySBBSTNode *)
	The private recursive call for setting the order of each node in the tree.
	Sets each height to the height of the right child - height of the left child, accounting for null children.
	After that it calls itself on both children.

	Input: MySBBSTNode *node: The node getting its order set.

	No return.

	Outcome: Once this recursive call is finished, each node on the tree has its correct order set.
*/
template <class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::order(MySBBSTNode *node)
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (node != NULL)
	{
		if (node->leftChild != NULL)
			leftHeight = node->leftChild->height;

		if (node->rightChild != NULL)
			rightHeight = node->rightChild->height;

		node->order = rightHeight - leftHeight;

		order(node->leftChild);
		order(node->rightChild);
	}
}

