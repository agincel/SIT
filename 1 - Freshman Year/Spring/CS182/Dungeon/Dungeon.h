#ifndef DUNGEON_H
#define DUNGEON_H

#include <string>
#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;
typedef unsigned int uint;

static const uint INF = -2147483646;
static const int intINF = -2147483646;

/*
Adam Gincel
Dungeon.h
This is the header of the Dungeon.

I pledge my honor that I have abided by the Stevens Honor System.
*/

class Dungeon
{
private:
	class Room
	{
	public:
		string name;
		string protectorName;
		uint protectorStrength;
		uint treasure;

		Room()
		{
			name = "Unconstructed Room";
			protectorName = "James Romph";
			protectorStrength = INF;
			treasure = INF;
		}

		Room(string n, string pN, uint pS, uint t)
		{
			name = n;
			protectorName = pN;
			protectorStrength = pS;
			treasure = t;
		}

		int lootRatio()
		{
			return treasure - protectorStrength;
		}
	};

	class Hero
	{
	public:
		string name;
		uint strength;
		uint health;

		Hero()
		{
			name = "Lol Null";
			strength = 0;
			health = 0;
		}

		Hero(string n, uint s, uint h)
		{
			name = n;
			strength = s;
			health = h;
		}
	};

	
	class myQueue
	{
	private:
		uint* theQueue;
		uint size;
		uint beginning;
		uint end;
	public:
		myQueue()
		{
			theQueue = new uint[999];
			beginning = 0;
			end = 0;
			size = 999;
		}

		myQueue(uint l)
		{
			theQueue = new uint[l];
			beginning = 0;
			end = 0;
			size = l;
		}

		void enqueue(uint i)
		{
			if (isFull())
			{
				cout << "Queue full.";
			}
			else
			{
				theQueue[end++] = i;
			}
		}


		bool isFull()
		{
			if (end == size)
				return true;
			else
				return false;
		}

		uint dequeue()
		{
			if (isEmpty())
				return INF;

			return theQueue[beginning++];
		}

		bool isEmpty()
		{
			if (beginning == end)
				return true;
			else
				return false;
		}
	};
	int lootRatio(uint s);

	void dfs(uint s);
	void bfs(uint s);

	uint* depthRoomsInt(uint s);
	void dfsInt(uint s);

	myQueue dfsQueue;

	bool allVisited();
	int getBestConnection(uint s);
	int getCombinedWeight(uint x, uint y);

	bool* visited;
	bool* visitedInner;

	myQueue bfsQueue;

	int** resNet;

	void print2DArray(uint** arr, uint size);
	void print2DArray(int** arr, uint size);

	void swap(uint x, uint y, uint*& arr);

	int* dijkstraReturn(uint s);

	uint uintLength(uint i);
	uint intLength(int i);

	uint myPizza(uint start, uint target, uint budget);

	bool fight(uint room);

	uint getStrongestHero();
	bool allHeroesDead();

	string randomOffenseVerb();


public:
	Room* roomList;
	uint roomListSize;

	int** adjacencyMatrix;
	uint adjacencyMatrixSize;

	Hero* heroList;
	uint heroListSize;
	uint totalHeroes;

	static uint heroCash;

	void styledPrint(string text, uint x);

	Dungeon()
	{
		roomListSize = 5;
		roomList = new Room[roomListSize];

		for (uint i = 0; i < roomListSize; i++)
		{
			roomList[i] = Room();
		}

		adjacencyMatrixSize = 5;
		adjacencyMatrix = new int*[adjacencyMatrixSize];

		for (uint i = 0; i < adjacencyMatrixSize; i++)
		{
			adjacencyMatrix[i] = new int[adjacencyMatrixSize];
			for (uint j = 0; j < adjacencyMatrixSize; j++)
			{
				adjacencyMatrix[i][j] = INF;
			}
		}

		heroListSize = 5;
		heroList = new Hero[heroListSize];

		for (uint i = 0; i < heroListSize; i++)
		{
			heroList[i] = Hero();
		}

		totalHeroes = 0;



		styledPrint("Dungeon Created", 1);
		
	}

	Dungeon(uint r, uint h)
	{
		//error checking
		if (r < 5)
			r = 5;

		if (h < 5)
			h = 5;

		roomListSize = r;
		roomList = new Room[roomListSize];

		adjacencyMatrixSize = r;
		adjacencyMatrix = new int*[adjacencyMatrixSize];
		for (uint i = 0; i < adjacencyMatrixSize; i++)
		{
			adjacencyMatrix[i] = new int[adjacencyMatrixSize];
			for (uint j = 0; j < adjacencyMatrixSize; j++)
			{
				adjacencyMatrix[i][j] = INF;
			}
		}

		heroListSize = h;
		heroList = new Hero[heroListSize];	
		
		for (uint i = 0; i < heroListSize; i++)
		{
			heroList[i] = Hero();
		}
		
		totalHeroes = 0;

		styledPrint("Dungeon Created", 1);
	}

	void listRooms();
	int addRoom(string name, string protectorName, uint strength, uint treasure);

	void showHalls();
	bool setHall(uint src, uint dst, uint cap);

	void showHeroes();
	bool addHero(string n, uint s, uint hp);

	void depthRooms();
	void printRoom(uint s);
	
	void breadthRooms();

	void mst();

	void lucrativePath(uint start);
	void lucrativePaths();
	uint pizzaParty(uint start, uint target, uint budget);

	void raid(uint start);

	




	



};










#endif