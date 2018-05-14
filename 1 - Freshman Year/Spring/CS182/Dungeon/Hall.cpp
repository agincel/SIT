#include "Dungeon.h"

/*
Adam Gincel
Hall.cpp
This contains methods pertaining to Halls, which are private data members of Dungeons.

I pledge my honor that I have abided by the Stevens Honor System.
*/


/**
showHalls()
A public method that lists all of the rooms in the adjacencyMatrix.

Input: None.

Returns: void, though prints the adjacencyMatrix.
*/
void Dungeon::showHalls()
{
	styledPrint("Hall List", 0);
	/*for (uint i = 0; i < adjacencyMatrixSize; i++)
	{
		for (uint j = 0; j < adjacencyMatrixSize; j++)
		{
			if (adjacencyMatrix[i][j] != INF)
				cout << adjacencyMatrix[i][j] << " ";
			else
				cout << "- ";
		}

		cout << endl;
	}*/

	print2DArray(adjacencyMatrix, roomListSize);

	cout << endl;

}


/**
setHall(uint src, uint dst, uint cap)
A public method that lets a user add a hallway between two edges (with valid input).

Input: uint src, uint dst, uint cap

Returns: bool: weather or not the edge was successfully added.
*/
bool Dungeon::setHall(uint src, uint dst, uint cap)
{
	//error checking
	if (src > roomListSize || dst > roomListSize)
		return false;
	if (src == dst)
		return false;


	if (cap == INF)
		cap = INF - 1;

	if (cap == 0)
		cap = INF;

	adjacencyMatrix[src][dst] = cap;
	return true;
}