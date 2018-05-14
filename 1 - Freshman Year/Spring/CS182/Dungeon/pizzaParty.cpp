#include "Dungeon.h"

/*
Adam Gincel
pizzaParty.cpp
This contains the modified Ford-Fulkerson method used to find a max-flow network, for pizza.

I pledge my honor that I have abided by the Stevens Honor System.
*/


/**
pizzaParty(uint start, uint target, uint budget)
A public method that determines the maximum amount of pizza that can be brought from a source room to a target room, given a certain budget.
It does this using the Ford-Fulkerson algorithm.

Input: uint start: the source node for the pizza
	   uint target: the resulting location of the pizza
	   uint budget: a limiting factor for the number of pizzas that can be delivered.


Returns: the max number of pizzas that can be brought from start to target, given uint budget.
*/
uint Dungeon::pizzaParty(uint start, uint target, uint budget)
{
	if (start == target)
	{
		//styledPrint("Pizza Party", 0);
		cout << "Max pizzas carryable from Room " << start << " to Room " << start << ": " << budget << endl << endl;
		return budget;
	}

	if (start > roomListSize || target > roomListSize)
	{
		//styledPrint("Pizza Party", 0);
		cout << "Invalid indices." << endl << endl;
		return 0;
	}
	
	visited = new bool[roomListSize];
	resNet = new int*[roomListSize];

	uint i, j;

	for (i = 0; i < roomListSize; i++)
	{
		visited[i] = false;
		resNet[i] = new int[roomListSize];
	}

	for (i = 0; i < roomListSize; i++)
	{
		for (j = 0; j < roomListSize; j++)
		{
			resNet[i][j] = adjacencyMatrix[j][i];
		}
	}

	uint sum = 0;
	uint temp;
	while (true)
	{
		for (i = 0; i < roomListSize; i++)
		{
			visited[i] = false;
		}

		temp = myPizza(target, start, budget);

		if (temp == 0)
		{
			if (sum > budget)
				sum = budget;

			break;
		}
		else
		{
			sum += temp;
		}
	}

	//styledPrint("Pizza Party", 0);
	//cout << "Max pizzas carryable from Room " << start << " to Room " << target << ": " << sum << endl << endl;

	return sum;

}

/**
myPizza(uint s)
A private recursive helper method that helps pizzaParty.

Input: uint start: the current starting point
	   uint target: end goal. If start == target, return.
	   uint budget: returned in base case.


Returns: max pizzas able to be brought between start and target.
*/
uint Dungeon::myPizza(uint start, uint target, uint budget)
{
	uint max;
	uint i;
	
	visited[start] = true;

	if (start == target)
	{
		return budget;
	}


	for (i = 0; i < roomListSize; i++)
	{
		if (!visited[i] && resNet[start][i] != 0 && resNet[start][i] != INF)
		{
			if (budget < resNet[start][i])
				max = budget;
			else
				max = resNet[start][i];

			max = myPizza(i, target, max);

			

			if (max > 0)
			{
				resNet[start][i] -= max;
				resNet[i][start] += max;

				return max;
			}
		}
	}

	return 0;
}
