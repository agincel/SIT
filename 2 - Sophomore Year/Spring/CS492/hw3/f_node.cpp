/*
	Adam Gincel - agincel
	hw3.c

	I pledge my honor that I have abided by the Stevens Honor System.
*/

#include "hw3.h"

F_Node::F_Node(int a)
{
	addr = a;
	previous = (F_Node *)0;
	next = (F_Node *)0;
}

void F_Node::addToEnd(int a)
{
	F_Node *currentNode = this;
	while(currentNode->next != 0)
		currentNode = currentNode->next;
	currentNode->next = new F_Node(a);
	currentNode->next->previous = currentNode;
}

int F_Node::getEndValue()
{
	F_Node *currentNode = this;
	while(currentNode->next != 0)
		currentNode = currentNode->next;
	return currentNode->addr;
}

void F_Node::deleteEnd()
{
	F_Node *currentNode = this;
	while(currentNode->next != 0)
	{
		currentNode = currentNode->next;
	}

	if(currentNode->previous != 0)
		currentNode->previous->next = (F_Node *)0;
	delete(currentNode);
}