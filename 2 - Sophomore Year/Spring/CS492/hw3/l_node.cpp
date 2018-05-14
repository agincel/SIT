/*
	Adam Gincel - agincel
	hw3.c

	I pledge my honor that I have abided by the Stevens Honor System.
*/

#include "hw3.h"


L_Node::L_Node(int l, int h)
{
	low = l;
	high = h;

	isUsed = false;

	previous = (L_Node *)0;
	next = (L_Node *)0;
}

void L_Node::addChild(int l, int h)
{
	L_Node *child = new L_Node(l, h);
	if(next != 0)
		next->previous = child;
	child->next = next;
	next = child;
	child->previous = this;
}

int L_Node::getFreeBlocks()
{
	int freeBlocks = 0;
	L_Node *currentNode = this;
	while(currentNode != 0)
	{
		if(!currentNode->isUsed)
		{
			freeBlocks += currentNode->high - currentNode->low + 1;
		}
		currentNode = currentNode->next;
	}
	return freeBlocks;
}