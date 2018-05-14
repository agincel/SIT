#include "Dungeon.h"

/*
Adam Gincel
Dungeon.cpp
This contains any variables/methods that don't belong in other files. Stylized print methods and miscellaneous helper methods are all here.

I pledge my honor that I have abided by the Stevens Honor System.
*/


uint Dungeon::heroCash = 0;

/**
styledPrint(string text, uint x)
A private method which prints out given text in a styled form.

Input: string text: Text to be displayed.
		uint x: the number of empty lines to be printed out after the styled text display.

Returns: void, though prints out stylized text.
*/
void Dungeon::styledPrint(string text, uint x)
{
	cout << "--------------------------------------------------" << endl;
	

	int maxSpaces = 25;

	//cout << "  ";

	int calc = maxSpaces - (text.length() / 2);

	uint i;


	for (i = 0; i < calc; i++)
	{
		cout << " ";
	}

	cout << text << endl << "--------------------------------------------------" << endl;


	for (uint i = 0; i < x; i++)
	{
		cout << endl;
	}
}

/**
lootRatio(uint s)
A private method which returns the lootRatio of a given room.

Input: uint s: The index of the room returning its lootRatio.


Returns: int, the lootRatio of room s.
*/
int Dungeon::lootRatio(uint s)
{
	if (s >= roomListSize)
		return 0;

	return roomList[s].lootRatio();
}

void Dungeon::print2DArray(uint** arr, uint size)
{
	uint i, j, k, z;
	uint max = 0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (arr[i][j] > max)
				max = arr[i][j];
		}
	}
	uint maxLength = uintLength(max) + 2;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			cout << "|";

			if (arr[i][j] != INF)
			{
				z = maxLength - (uintLength(arr[i][j]));

				for (k = 0; k < z; k++)
					cout << " ";

				cout << arr[i][j];

				if (maxLength % 2 == 1)
					z--;

				for (k = 0; k < z; k++)
					cout << " ";
			}
			else
			{
				z = maxLength - 1;

				for (k = 0; k < z; k++)
					cout << " ";

				cout << "-";

				for (k = 0; k < z; k++)
					cout << " ";
			}
		}

		cout << "|" << endl;
	}
}


/**
print2DArray(string text, uint x)
A private method which prints out a given 2D array

Input: string text: Text to be displayed.
uint x: the number of empty lines to be printed out after the styled text display.

Returns: void, though prints out stylized text.
*/
void Dungeon::print2DArray(int** arr, uint size)
{
	uint i, j, k;
	int z, max = 0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (abs(arr[i][j]) > abs(max) && arr[i][j] != INF)
				max = arr[i][j];
		}
	}
	uint maxLength = intLength(abs(max)) + 2;

	if (max < 0)
		maxLength++;

	uint innerLength;
	bool innerLengthEven;
	bool maxLengthEven = (maxLength % 2 == 0);

	cout << "x\\y   ";

	

	for (i = 0; i < size; i++) //top row of indices
	{
		innerLength = intLength(i);
		innerLengthEven = (innerLength % 2 == 0);

		if (maxLengthEven)
		{
			if (innerLengthEven)
			{
				z = ((maxLength - innerLength) / 2);
			}
			else
			{
				z = ((maxLength - innerLength) / 2) + 1;
			}
		}
		else
		{
			if (innerLengthEven)
			{
				z = ((maxLength - innerLength) / 2) + 1;
			}
			else
			{
				z = ((maxLength - innerLength) / 2);
			}
		}

		cout << " ";

		for (k = 0; k < z; k++)
			cout << " ";
		
		cout << i;


		z = ((maxLength - innerLength) / 2);

		for (k = 0; k < z; k++)
			cout << " ";

		
	}

	string asdf;


	cout << endl << endl;

	for (i = 0; i < size; i++)
	{
		cout << i << ":    ";
		
		for (j = 0; j < size; j++)
		{
			cout << "|";
			if (arr[i][j] != INF)
			{
				innerLength = intLength(arr[i][j]);
				if (arr[i][j] < 0)
					innerLength++;

				innerLengthEven = (innerLength % 2 == 0);

				if (maxLengthEven)
				{
					if (innerLengthEven)
					{
						z = ((maxLength - innerLength) / 2);
					}
					else
					{
						z = ((maxLength - innerLength) / 2) + 1;
					}
				}
				else
				{
					if (innerLengthEven)
					{
						z = ((maxLength - innerLength) / 2) + 1;
					}
					else
					{
						z = ((maxLength - innerLength) / 2);
					}
				}

				for (k = 0; k < z; k++)
					cout << " ";

				cout << arr[i][j];

				z = ((maxLength - innerLength) / 2);

				for (k = 0; k < z; k++)
					cout << " ";
				
			}
			else
			{
				if (maxLengthEven)
				{
					asdf = "--";
					innerLength = 2;
				}
				else
				{
					asdf = "-";
					innerLength = 1;
				}

				z = ((maxLength - innerLength) / 2);

				for (k = 0; k < z; k++)
					cout << " ";

				cout << asdf;

				for (k = 0; k < z; k++)
					cout << " ";
			}
		}
		cout << "|" << endl;

		if (i < size - 1)
		{
			cout << "      ";
			for (k = 0; k < size; k++)
			{
				for (uint idk = 0; idk <= maxLength; idk++)
					cout << "-";
			}
			cout << "-" << endl;
		}

	}

}

uint Dungeon::uintLength(uint i)
{
	return (uint)log10((double) i) + 1;
}

uint Dungeon::intLength(int i)
{
	return (uint)log10((double) abs(i)) + 1;
}










