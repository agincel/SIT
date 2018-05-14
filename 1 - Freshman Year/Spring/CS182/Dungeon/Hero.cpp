#include "Dungeon.h"

/*
Adam Gincel
Hero.cpp
This contains methods pertaining to Heroes, which are private data members of Dungeons.

I pledge my honor that I have abided by the Stevens Honor System.
*/

/**
addHero(string n, uint s, uint hp)
A public method that lets a user add a Hero to the heroList with certain stats.

Input: string n: name, uint s: strength, uint hp: health

Returns: bool: weather or not the hero was successfully added.
*/
bool Dungeon::addHero(string n, uint s, uint hp)
{
	if (hp == 0 || hp == INF || s == INF || s == 0)
		return false;

	for (uint i = 0; i < heroListSize; i++)
	{
		//cout << i << endl;
		if (heroList[i].health == 0)
		{
			heroList[i] = Hero(n, s, hp);
			totalHeroes++;
			return true;
		}
	}

	return false;
}

/**
showHeroes()
A public method that lists all of the rooms in the heroList.

Input: None.

Returns: void, though prints the heroList.
*/
void Dungeon::showHeroes()
{
	styledPrint("Hero List", 0);
	for (uint i = 0; i < heroListSize; i++)
	{
		if (heroList[i].health == 0)
			cout << "Party slot " << i << ": " << endl << "\tNo hero in this party slot!" << endl;
		else
		{
			cout << "Party slot " << i << ": " << endl;
			cout << "\tName: " << heroList[i].name << endl;
			cout << "\tStrength: " << heroList[i].strength << endl;
			cout << "\tHP: " << heroList[i].health << endl;
		}

		cout << endl;
	}
	cout << "Party Cash ($): " << heroCash << endl;
	cout << endl;
}