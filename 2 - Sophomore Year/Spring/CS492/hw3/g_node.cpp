/*
	Adam Gincel - agincel
	hw3.c

	I pledge my honor that I have abided by the Stevens Honor System.
*/

#include "hw3.h"

G_Node::G_Node(string n, bool isL)
{
	name = n;
	isFile = isL;
	parent = (G_Node *)0;
}

void G_Node::addChild(G_Node* child)
{
	child->parent = this;
	if(!isFile)
	{
		children.push_back(child);
	}
}

void G_Node::addFileInfo(int bN)
{
	bytesNeeded = bN;
	fileSpace = (F_Node *)0;
}

string G_Node::getPath()
{
	vector<string> path;
	path.push_back(name);
	G_Node *currentNode = parent;
	string ret = "";
	while(currentNode != 0)
	{
		path.push_back(currentNode->name);
		currentNode = currentNode->parent;
	}

	for(int i = path.size() - 1; i >= 0; i--)
	{
		ret = ret + path[i];
		if(!(i == 0 && isFile))
			ret += "/";
	}
	return ret;
}

int G_Node::blocksPossessed()
{
	int count = 0;
	F_Node *currentNode = fileSpace;
	while(currentNode != 0)
	{
		count++;
		currentNode = currentNode->next;
	}
	return count;
}