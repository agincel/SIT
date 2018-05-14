#include "Dungeon.h"

/*
Adam Gincel
bfs.cpp
This contains methods pertaining to Breadth First Search.

I pledge my honor that I have abided by the Stevens Honor System.
*/


/**
breadthRooms()
A public method with no parameters that uses its helper methods to print out a Breadth First Search.

Input: None

Returns: void, though prints out a BFS.
*/
void Dungeon::breadthRooms()
{
	styledPrint("Breadth First Search", 0);

	bool hasTraversed = false;

	visited = new bool[roomListSize];
	bfsQueue = myQueue(roomListSize);

	for (uint i = 0; i < roomListSize; i++)
	{
		visited[i] = false;
	}

	for (uint i = 0; i < roomListSize; i++)
	{
		if (!visited[i] && roomList[i].treasure != INF)
		{
			if (hasTraversed)
				cout << "------" << endl;
			bfs(i);
			hasTraversed = true;

		}
	}

	cout << endl;
}

/**
bfs(uint s)
A private method that uses a queue to output a BFS.

Input: uint s: the starting node of the BFS.

Returns: void, though prints out an BFS.
*/
void Dungeon::bfs(uint s)
{
	if (!visited[s])
	{
		bfsQueue.enqueue(s);
		printRoom(s);
		visited[s] = true;
	}

	while (!bfsQueue.isEmpty())
	{
		s = bfsQueue.dequeue();

		for (uint i = 0; i < roomListSize; i++)
		{
			if (!visited[i] && adjacencyMatrix[s][i] != INF)
			{
				bfsQueue.enqueue(i);
				visited[i] = true;
				printRoom(i);
			}
		}
	}
}