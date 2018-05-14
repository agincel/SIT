#include "Dungeon.h"

/*
Adam Gincel
dfs.cpp
This contains methods pertaining to Depth First Search.

I pledge my honor that I have abided by the Stevens Honor System.
*/

/**
depthRooms()
A public method with no parameters that uses its helper methods to print out a Depth First Search

Input: None

Returns: void, though prints out a DFS.
*/
void Dungeon::depthRooms()
{
	styledPrint("Depth First Search", 0);

	visited = new bool[roomListSize];

	bool hasTraversed = false;

	for (uint i = 0; i < roomListSize; i++)
	{
		visited[i] = false;
	}

	for (uint i = 0; i < roomListSize; i++)
	{
		if (!visited[i] && roomList[i].treasure != INF)
		{
			if (hasTraversed)
				cout << "---------" << endl;
			dfs(i);
			hasTraversed = true;
		}
	}

	cout << endl;
}

/**
dfs(uint s)
A private recursive method that outputs a DFS.

Input: uint s: the node currently being visited.

Returns: void, though prints out an DFS.
*/
void Dungeon::dfs(uint s)
{
	if (s < roomListSize && !visited[s])
	{
		visited[s] = true;
		printRoom(s);

		for (uint i = 0; i < roomListSize; i++)
		{
			if (!visited[i] && adjacencyMatrix[s][i] != INF)
			{
				dfs(i);
			}
		}
	}
}


/**
depthRoomsInt(uint s)
A private method used in raid that does a DFS only once from a specified starting node. 

Input: uint s: starting index.

Returns: uint*, the array of indices visited in that order.
*/
uint* Dungeon::depthRoomsInt(uint s)
{
	//styledPrint("Depth First Search", 0);
	uint* result = new uint[roomListSize];

	visited = new bool[roomListSize];
	uint i = 0;
	for (i = 0; i < roomListSize; i++)
		visited[i] = false;

	dfsQueue = myQueue(roomListSize);

	if (roomList[s].treasure != INF)
	{
		//cout << "roomList[0].treasure != INF" << endl;
		dfsInt(s);
	}
	
	for (i = 0; i < roomListSize; i++)
	{
		result[i] = dfsQueue.dequeue();
	}

	return result;
}

/**
dfsInt(uint s)
A private recursive method that enqueues a DFS.

Input: uint s: the node currently being visited.

Returns: void, though enqueues a DFS.
*/
void Dungeon::dfsInt(uint s)
{
	if (s < roomListSize && !visited[s])
	{
		visited[s] = true;
		dfsQueue.enqueue(s);
		//cout << s << endl;

		for (uint i = 0; i < roomListSize; i++)
		{
			if (!visited[i] && adjacencyMatrix[s][i] != INF)
			{
				dfsInt(i);
			}
		}
	}
}