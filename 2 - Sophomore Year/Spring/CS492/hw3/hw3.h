/*
	Adam Gincel - agincel
	hw3.c

	I pledge my honor that I have abided by the Stevens Honor System.
*/

#ifndef HW3_H
#define HW3_H

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <list>
#include <sstream>

using namespace std;

class L_Node
{
	public:
		L_Node(int l, int h);
		void addChild(int l, int h);
		int getFreeBlocks();

		int low;
		int high;
		bool isUsed;

		L_Node *previous;
		L_Node *next;
};

class F_Node
{
	public:
		F_Node(int a);
		void addToEnd(int a);
		int getEndValue();
		void deleteEnd();

		int addr;
		F_Node *previous;
		F_Node *next;
};

class G_Node
{
	public:
		G_Node(string n, bool isL);
		void addChild(G_Node* child);
		string getPath();
		void addFileInfo(int bN);
		int blocksPossessed();

		bool isFile;
		vector<G_Node*> children;
		string name;
		G_Node *parent;
		F_Node *fileSpace;
		int bytesNeeded;
};

vector<string> splitByCharacter(string toSplit, char byChar);
G_Node* getNodeByName(vector<G_Node*> children, string name);
int getNodeIndexByName(vector<G_Node*> children, string name);
void printDirectory(G_Node *root);
void error(string msg);
void printVector(vector<string> blah);

int consumeBlock(L_Node *root);
int removeBlock(L_Node *root, int addr);
void printLNodes(L_Node *root);
int getBlocksNeeded(int bytesNeeded);


int getDiskSize();
int getBlockSize();


#endif
