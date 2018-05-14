#include "Dungeon.h"

/*
Adam Gincel
mst.cpp
This contains methods pertaining to Maximum Spanning Trees, specifically Primm's Algorithm.

I pledge my honor that I have abided by the Stevens Honor System.
*/


/**
mst()
A public method with no parameters that uses its helper methods to output a Maximum Pizza Spanning Tree.

Input: None

Returns: void, though prints out an MST.
*/
void Dungeon::mst()
{
	styledPrint("Most Pizza Spanning Tree", 0);

	uint i;

	visited = new bool[roomListSize];
	for (i = 0; i < roomListSize; i++)
	{
		visited[i] = false;
	}

	visited[0] = true;

	while (!allVisited())
	{
		int v = getBestConnection(0);
		
		

		if (v == INF)
		{
			cout << "Disconnected graph." << endl;
			return;
		}

		visited[v] = true;
	}

	cout << endl;
}


/**
allVisited()
A private method with no parameters that returns a boolean reflecting whether or not visited[] is entirely true.

Input: None

Returns: true or false, depending on whether or not visited[] is entirely true or not.
*/
bool Dungeon::allVisited()
{
	for (uint i = 0; i < roomListSize; i++)
	{
		if (!visited[i])
			return false;
	}

	return true;
}


/**
getBestConnection(uint s)
A private method that takes in a host point as a parameter, and returns the index of the highest valued connection from that node.

Input: uint s: the index from which we are looking for a connection.

Returns: uint, the index of the best connection
*/
int Dungeon::getBestConnection(uint s)
{
	int highestEdgeIndex = 0;
	int col = 0, row = 0;

	int highestEdge = INF;

	uint i, j;

	for (i = 0; i < roomListSize; i++)
	{
		for (j = 0; j < roomListSize; j++)
		{
			if (visited[i] && !visited[j])
			{
				if (getCombinedWeight(i, j) != INF && getCombinedWeight(i, j) > highestEdge)
				{
					row = i;
					col = j;
					highestEdgeIndex = col;
					highestEdge = getCombinedWeight(i, j);
				}
			}
		}
	}

	if (highestEdge == INF)
		return INF;
	
	if (roomList[col].treasure != INF)
		cout << row << " -- " << getCombinedWeight(row, col) << " --> " << col << endl;



	return highestEdgeIndex;
}


/**
getCombinedWeight(uint x, uint y)
A private method that gets the combined weight to and from two nodes.

Input: uint x and y: the indices of the source and destination.

Returns: int, the combined weight between x and y in the adjacency matrix.
*/
int Dungeon::getCombinedWeight(uint x, uint y)
{
	uint weight = 0;

	if (adjacencyMatrix[x][y] != INF)
		weight += adjacencyMatrix[x][y];

	if (adjacencyMatrix[y][x] != INF)
		weight += adjacencyMatrix[y][x];

	if (weight == 0)
		return -1;
	return weight;
}
