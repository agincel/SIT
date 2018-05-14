#ifndef _MYSBBST_H_
#define _MYSBBST_H_

#include <iostream>
#include <cstring>
#include "student.hh"
using namespace std;
/*
Adam Gincel
MySBBST.h
This is the header of the AVL tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/

template <class Elem, class Key, class EEComp, class KEComp>
class MySBBST
{
private:
	class MySBBSTNode
	{
	public:
		Elem data;
		int height;
		int order;
		MySBBSTNode *leftChild;
		MySBBSTNode *rightChild;
		MySBBSTNode(Elem e)
		{
			data = e;
			leftChild = NULL;
			rightChild = NULL;
			height = 0;
			order = 0;
		}
	};

	bool add(MySBBSTNode *&, Elem);
	Elem search(MySBBSTNode *, Key);
	Elem remove(MySBBSTNode *&, Key);
	Elem removeMin(MySBBSTNode *&);
	void printout(MySBBSTNode *);
	int height(MySBBSTNode *);
	int height();
	void order(MySBBSTNode *);
	void order();
	void rotateLeft(MySBBSTNode *&);
	void rotateRight(MySBBSTNode *&);
	void problemCheck();
	void problemCheck(MySBBSTNode *&);
	MySBBSTNode *root;
	bool isValidTree(MySBBSTNode *);
	Elem zero;

public:
	bool add(Elem);
	Elem search(Key);
	Elem remove(Key);
	void printout();
	bool isValidTree();
	

	MySBBST(Elem z)
	{
		root = NULL;
		zero = z;
	}
	
};

class intintCompare
{
 public:
  static bool lt(int, int);
  static bool gt(int, int);
  static bool eq(int, int);
};







#endif
