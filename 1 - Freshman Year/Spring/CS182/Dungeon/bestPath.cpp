#include "Dungeon.h"

/*
Adam Gincel
bestPath.cpp
This contains all methods relating to Dijkstra's Algorithm and Floyd's Algorithm. Contains a modified dijkstra used as a helper for Floyd's algorithm.

I pledge my honor that I have abided by the Stevens Honor System.
*/


/**
lucrativePath(uint s)
A public method that prints out the results of Dijkstra's Algorithm, with starting source index s.

Input: uint s: the source node for dijkstra.

Returns: void, though prints out text.
*/
void Dungeon::lucrativePath(uint s)
{
	if (s >= roomListSize || roomList[s].treasure == INF)
	{
		cout << "Invalid room index." << endl;
		return;
	}

	string output = "Lucrative Path From " + roomList[s].name;
	styledPrint(output, 0);

	int* D = new int[roomListSize];
	uint* unvisited = new uint[roomListSize];

	uint i;
	for (i = 0; i < roomListSize; i++)
	{
		D[i] = INF;
		unvisited[i] = i;
	}

	D[s] = 0;

	int todo = roomListSize;
	uint max = s;

	while (todo > 1)
	{
		for (i = 0; i < todo; i++)
		{
			if (D[unvisited[i]] > D[unvisited[max]] || (((D[unvisited[max]] == INF) || max >= todo) && D[unvisited[i]] != INF)) //if unvisited[i] has index for better value, or if we have no value but i gives us one
			{
				max = i;
			}
		}

		swap(max, --todo, unvisited);

		for (i = 0; i < todo; i++)
		{
			//cout << "un[todo] = " << unvisited[todo] << " | un[i] = " << unvisited[i] << " | adjMat[un[todo]][un[i]] = " << adjacencyMatrix[unvisited[todo]][unvisited[i]] << endl;
			if (adjacencyMatrix[unvisited[todo]][unvisited[i]] != INF) //edge from todo to i exists
			{
				if (D[unvisited[i]] == INF || D[unvisited[i]] < D[unvisited[todo]] + lootRatio(unvisited[i])) //if no path existed, or current path is better than existing path
				{
					//uint debug = D[unvisited[todo]];
					D[unvisited[i]] = D[unvisited[todo]] + lootRatio(unvisited[i]);
					//cout << "i = " << i << " | Setting " << unvisited[i] << " to " << debug << " + " << roomList[unvisited[i]].treasure << " - " << roomList[unvisited[i]].protectorStrength << endl;
				}
			}
		}
	}

	for (i = 0; i < roomListSize; i++)
	{
		if (i != s)
		{
			if (D[i] == INF)
			{
				if (roomList[i].treasure != INF)
					cout << "No path to Room " << i << "." << endl;
				else
					cout << "Room " << i << " doesn't exist!" << endl;
			}
			else
				cout << "Most Lucrative Path to Room " << i << ": " << D[i] << endl;
		}
	}

	cout << endl;
}

/**
dijkstraReturn(uint s)
A private method that returns the results of Dijkstra's Algorithm as an int*, with starting source index s.

Input: uint s: the source node for dijkstra.

Returns: int*, the lootRatio array from index s.
*/
int* Dungeon::dijkstraReturn(uint s)
{

	uint i;
	if (s >= roomListSize || roomList[s].treasure == INF) //return if room is out of bounds or doesn't exist
	{
		int* derp = new int[roomListSize];
		for (i = 0; i < roomListSize; i++)
			derp[i] = INF;
		return derp;
	}

	int* D = new int[roomListSize];
	uint* unvisited = new uint[roomListSize];


	for (i = 0; i < roomListSize; i++)
	{
		D[i] = INF;
		unvisited[i] = i;
	}

	D[s] = 0;

	int todo = roomListSize;
	uint max = s;

	while (todo > 1)
	{
		for (i = 0; i < todo; i++)
		{
			if (D[unvisited[i]] > D[unvisited[max]] || (((D[unvisited[max]] == INF) || max >= todo) && D[unvisited[i]] != INF))
			{
				max = i;
			}
		}

		swap(max, --todo, unvisited);

		for (i = 0; i < todo; i++)
		{
			if (adjacencyMatrix[unvisited[todo]][unvisited[i]] != INF)
			{

				if ((D[unvisited[i]] == INF || D[unvisited[i]] < D[unvisited[todo]] + lootRatio(unvisited[i])) && roomList[i].treasure != INF)
				{
					//uint debug = D[unvisited[todo]];
					D[unvisited[i]] = D[unvisited[todo]] + lootRatio(unvisited[i]);
					//cout << "i = " << i << " | Setting " << unvisited[i] << " to " << debug << " + " << roomList[unvisited[i]].treasure << " - " << roomList[unvisited[i]].protectorStrength << endl;
				}
			}
		}
	}

	return D;
}


/**
swap(uint x, uint y, uint*& arr)
A private method that swaps two indices in a uint*.

Input: uint x: first index to swap.
	   uint y: second index to swap.
	   uint*& arr: array which is getting swapped.


Returns: void. Swaps the array's indices.
*/
void Dungeon::swap(uint x, uint y, uint*& arr)
{
	uint temp = arr[y];

	arr[y] = arr[x];

	arr[x] = temp;
}


/**
lucrativePaths()
A public method that prints out the results of Floyd's Algorithm. Uses a modified Dijkstra as a helper method.

Input: none.


Returns: void, though prints out a matrix of the results of Floyd.
*/
void Dungeon::lucrativePaths() //Floyd's Algorithm
{
	int** resultMatrix = new int*[roomListSize];
	uint i;

	for (i = 0; i < roomListSize; i++)
	{
		resultMatrix[i] = dijkstraReturn(i);
	}

	styledPrint("Lucrative Rooms Matrix", 0);

	print2DArray(resultMatrix, roomListSize);

	cout << endl;
}
