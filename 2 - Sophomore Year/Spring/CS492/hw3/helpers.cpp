#include "hw3.h"

/*
	Adam Gincel - agincel
	helpers.cpp

	I pledge my honor that I have abided by the Stevens Honor System.
*/


vector<string> splitByCharacter(string toSplit, char byChar)
{
	bool escaped = false;
	vector<string> ret;
	string build = "";
	for(int i = 0; i < toSplit.length(); i++)
	{
		if(toSplit[i] == byChar && !escaped) //time to split
		{
			if (build.compare("") != 0) //real string to show
			{
				ret.push_back(build);
				build = "";
			}
		}
		else if(toSplit[i] == '\\') //if we have a backslash, set escaped to true and add the \ to the string
		{
			escaped = true;
			build += toSplit[i];
		}
		else //any other character
		{
			escaped = false;
			build += toSplit[i];
		}
	}
	if(build.compare("") != 0) //still something left in string
		ret.push_back(build);
	return ret;
}

G_Node* getNodeByName(vector<G_Node*> children, string name)
{
	for(int i = 0; i < children.size(); i++)
	{
		if(children[i]->name.compare(name) == 0) //found it
		{
			return children[i];
		}
	}
	return (G_Node *)0;
}

int getNodeIndexByName(vector<G_Node*> children, string name)
{
	for(int i = 0; i < children.size(); i++)
	{
		if(children[i]->name.compare(name) == 0) //found it
		{
			return i;
		}
	}
	return -1;
}

void printDirectory(G_Node* root)
{
	vector<G_Node*> myQueue;
	G_Node* current;
	current = root;
	myQueue.push_back(current); //enqueue

	cout << current->getPath() << "\n"; //print root

	while(myQueue.size() > 0)
	{
		current = myQueue[0];
		myQueue.erase(myQueue.begin()); //dequeue

		for(int i = 0; i < current->children.size(); i++)
		{
			cout << current->children[i]->getPath() << "\n";
			myQueue.push_back(current->children[i]);
		}
	}
}

void error(string msg)
{
	cout << msg << "\n";
	exit(1);
}

void printVector(vector<string> blah)
{
	cout << "-----\n";
	for(int i = 0; i < blah.size(); i++)
		cout << blah[i] << endl;
	cout << "-----\n";	
}

int getBlocksNeeded(int bytes)
{
	return ceil((double)bytes / (double)getBlockSize());
}

int consumeBlock(L_Node *root) //returns address of block taken, -1 if all blocks full
{							   //also performs all L_Node operations (merging, splitting)
	L_Node *currentNode = root;
	int blockAddr = -1;
	//cout << "Looking for free node.\n";
	while(currentNode != 0 && currentNode->isUsed) //find unused node
		currentNode = currentNode->next;
	//cout << "Found free node.\n";
	if(currentNode != 0) //found valid, unused node
	{
		//cases
		if(currentNode->previous == 0) //we're first, send the unused forwards
		{
			if(currentNode->low == currentNode->high) //if only one left, merge next node into us
			{
				//[0,0]f->[1,10]u becomes [0,10]u
				if(currentNode->next != 0) //if we have a next
				{
					blockAddr = currentNode->low;
					currentNode->high = currentNode->next->high;
					currentNode->isUsed = true;
					L_Node *toDelete = currentNode->next;
					currentNode->next = currentNode->next->next;
					if(currentNode->next != 0)
						currentNode->next->previous = currentNode;
					delete(toDelete);
				}
				else //one one-block node??
				{
					blockAddr = currentNode->low;
					currentNode->isUsed = true;
				}
			}
			else
			{
				//[0, 5]f->[6,10]u becomes [0,0]u->[1,5]f->[6,10]u
				blockAddr = currentNode->low;
				currentNode->addChild(currentNode->low + 1, currentNode->high);
				currentNode->high = currentNode->low;
				currentNode->isUsed = true;
			}
		}
		else if(currentNode->next == 0) //we're last, send the one used backwards (previous has to exist)
		{
			if(currentNode->low == currentNode->high)
			{
				//[0,9]u->[10,10]f becomes [0,10]u
				blockAddr = currentNode->low;
				currentNode->previous->high++;
				currentNode->previous->next = (L_Node *)0; //forget about us
				delete(currentNode);
			}
			else
			{
				//[0, 5]u->[6, 10]f becomes [0, 6]u->[7, 10]f
				blockAddr = currentNode->low;
				currentNode->previous->high++;
				currentNode->low++;
			}
		}
		else //we're somewhere in the middle; both previous and next have to exist
		{
			if(currentNode->low == currentNode->high) //hoo boy
			{
				//[0,2]u->[3,3]f->[4,10]u becomes [0,10]u
				//set previous->high to next->high, set previous-> next = next->next, if next->next exists set next->next->previous to previous
				blockAddr = currentNode->low;
				currentNode->previous->high = currentNode->next->high;
				currentNode->previous->next = currentNode->next->next;
				if(currentNode->next->next != 0)
					currentNode->next->next->previous = currentNode->previous;
				delete(currentNode->next);
				delete(currentNode);
			}
			else
			{
				//[0,3]u->[4,6]f->[7,10]u becomes [0,4]u->[5,6]f->[7,10]u
				blockAddr = currentNode->low;
				currentNode->previous->high++;
				currentNode->low++;
			}
		}

		return blockAddr;
	}
	else //all nodes used
	{
		return -1;
	}
}

int removeBlock(L_Node *root, int addr)
{
	L_Node *currentNode = root;
	int ret = -1;
	bool foundBlock = false;
	while(!foundBlock) //find block
	{
		if(currentNode != 0) //if we still have nodes
		{
			if(addr >= currentNode->low && addr <= currentNode->high) //the addr is in this node
			{
				if(currentNode->isUsed) //this addr isn't already free for some reason
					foundBlock = true;
				else
				{
					cout << "Node to remove addr already free?\n";
					return -1;
				}
			}
			else
			{
				currentNode = currentNode->next;
			}
		}
		else
		{
			cout << "Node to remove addr out of range?\n";
			return -1;
		}
	}

	if(currentNode->low == currentNode->high) //if we're in a singleton node
	{
		if(currentNode->previous != 0 && currentNode->next != 0) //exist on either side of us
		{
			//[0,1]f->[2,2]u->[3,4]f becomes [0,6]f
			currentNode->previous->high = currentNode->next->high;
			currentNode->previous->next = currentNode->next->next;
			if(currentNode->next->next != 0)
				currentNode->next->next->previous = currentNode->previous;
			delete(currentNode->next);
			delete(currentNode);
			ret = addr;
		}
		else if(currentNode->previous != 0) //we have just a left
		{
			//[0, 9]f->[10,10]u becomes [0, 10]f
			currentNode->previous->high++;
			currentNode->previous->next = (L_Node *)0;
			delete(currentNode);
			ret = addr;
		}
		else if(currentNode->next != 0) //we only have a right
		{
			//[0,0]u->[1,10]f becomes [0,10]f
			currentNode->high = currentNode->next->high;
			currentNode->isUsed = false;
			L_Node *toDelete = currentNode->next;
			currentNode->next = currentNode->next->next;
			if(currentNode->next != 0)
				currentNode->next->previous = currentNode;
			delete(toDelete);
			ret = addr;
		}
		else //there's only a single block?
		{
			currentNode->isUsed = false;
			ret = addr;
		}
	}
	else if(addr == currentNode->low) //we're first
	{
		if(currentNode->previous == 0) //this node is the first in the list
		{
			//[0, 10]u->[11,15]f becomes [0,0]f->[1,10]u->[11,15]f
			currentNode->addChild(currentNode->low + 1, currentNode->high);
			currentNode->next->isUsed = true;
			currentNode->isUsed = false;
			ret = addr;
		}
		else //a previous node exists
		{
			//[0,5]f->[6,10]u becomes [0,6]f->[7,10]u
			currentNode->previous->high++;
			currentNode->low++;
			ret = addr;
		}
	}
	else if(addr == currentNode->high) //we're last
	{
		if(currentNode->next == 0) //node is last
		{
			//[0,5]f->[6,10]u becomes [0,5]f->[6,9]u->[10,10]f
			currentNode->addChild(currentNode->high, currentNode->high);
			currentNode->high--;
			ret = addr;
		}
		else //there's something after this node
		{	
			//[0,5]f->[6,9]u->[10,10]f becomes [0,5]f->[6,8]u->[9,10]f
			currentNode->next->low--;
			currentNode->high--;
			ret = addr;
		}
	}
	else //we're somewhere in the middle of a node with >= 3 blocks
	{
		//7: [0,5]f->[6,9]u->[10,10]f becomes [0,5]f->[6,6]u->[7,7]f->[8,9]u->[10,10]f
		currentNode->addChild(addr + 1, currentNode->high);
		currentNode->next->isUsed = true;
		currentNode->addChild(addr, addr);
		currentNode->high = addr - 1;
		ret = addr;
	}

	return ret;
}

string intToString(int a)
{
	string s;
	stringstream out;
	out << a;
	s = out.str();
	return s;
}

void printLNodes(L_Node *root)
{
	L_Node *currentNode = root;
	string s = "";
	while(currentNode != 0)
	{
		s = "[" + intToString(currentNode->low) + ", " + intToString(currentNode->high) + "]";
		s += currentNode->isUsed ? "used->" : "free->";
		cout << s;
		currentNode = currentNode->next;
	}
	cout << "NULL\n";
}

