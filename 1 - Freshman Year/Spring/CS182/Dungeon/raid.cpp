#include "Dungeon.h"
#include <limits>

#ifdef _WIN32
#include <windows.h>

void usleep(int time)
{
	Sleep(time / 1000); //now calling usleep works on windows and unix
}

#else
#include <unistd.h>
#endif

int longDelay = 2100000;
int shortDelay = 2000000;

/*
Adam Gincel
raid.cpp
This contains the methods involved with the Dungeon Raid method.

I pledge my honor that I have abided by the Stevens Honor System.
*/

void Dungeon::raid(uint start)
{
	longDelay = 2100000;
	shortDelay = 2000000;
	
	
	if (start > roomListSize || roomList[start].treasure == INF)
	{
		cout << "Invalid starting room!" << endl;
		return;
	}

	if (totalHeroes == 0)
	{
		cout << "You have no heroes to run the dungeon!" << endl;
		return;
	}
	int input = 0;

	cout << "Would you like delays between each line of text? Enter 0 for yes, anything else for no." << endl;

	uint why = -1;
	if(!(cin >> input) || input != 0) {
		cin.clear();
		cin.ignore(why, '\n');
		shortDelay = 0;
		longDelay = 0;
	}


	



	uint i; //storage to reset rooms
	Room* roomListStorage = new Room[roomListSize];
	for (i = 0; i < roomListSize; i++)
		roomListStorage[i] = roomList[i];

	Hero* heroListStorage = new Hero[heroListSize];
	for (i = 0; i < heroListSize; i++)
		heroListStorage[i] = heroList[i];

	bool canContinue;
	uint lastVisitedRoom = start;

	uint* indices = depthRoomsInt(start);

	//Story time!
	uint storyIndex = 0;

	styledPrint("Raid Simulation", 0);
	usleep(longDelay/2);

	if (totalHeroes == 1) //hero flying solo
	{
		cout << "Our story begins with " << heroList[0].name << " navigating a dungeon solo. They think they're so tough, they left their friends behind." << endl;
		usleep(shortDelay);
		cout << "\"Alright," << heroList[0].name << ", you've got this. You don't know the targets, and they don't know you. This is just business." << endl;
		usleep(shortDelay);
	}
	else //hero party > 1
	{

		cout << "Our story begins with ";
		for (i = 0; i < totalHeroes - 1; i++)
		{
			cout << heroList[i].name;
			
			if (totalHeroes == 2)
				cout << " ";
			else
				cout << ", ";
		}

		cout << "and " << heroList[i].name << " navigating a dungeon together." << endl;
		usleep(shortDelay);

		cout << "\"Are you sure the bosses said we had to leave no witnesses?\" " << heroList[0].name << " asked. " << endl;
		usleep(shortDelay);

		cout << "\"Yup. They told us to order pizza too, which makes sense.\" " << heroList[1].name << " replied." << endl;
		usleep(shortDelay);

		if (totalHeroes > 2)
			storyIndex = 2;
		else
			storyIndex = 0;

		cout << "\"Alright,\" said " << heroList[storyIndex].name << ". \"Enough talk. Time to get this party started.\"" << endl << endl;
		usleep(shortDelay / 2);	

		storyIndex = getStrongestHero();

		cout << heroList[storyIndex].name << ", clearly the strongest, took the lead." << endl;
		usleep(shortDelay);
	}
 


	for (i = 0; i < roomListSize; i++)
	{
		if (indices[i] != INF)
		{
			if (roomList[indices[i]].treasure != INF)
			{
				canContinue = fight(indices[i]); //go through all rooms in index order, wrapping around if needed.
				lastVisitedRoom = indices[i];
			}
			else
				canContinue = true;

			if (!canContinue)
			{
				cout << "\nAll of the heroes have fallen. No pizza will be had today." << endl;
				styledPrint("Game Over", 1);
				return;
			}
		}
	}

	styledPrint("Results", 0);
	usleep(shortDelay);

	cout << "The heroes ended in " << roomList[lastVisitedRoom].name << " and have " << heroCash << " gold coins. Pizza time!" << endl;
	usleep(longDelay);

	uint numPizzas = pizzaParty(start, lastVisitedRoom, heroCash);
	cout << "The heroes ordered a total of " << numPizzas << " pizzas from the " << roomList[start].name << " to the " << roomList[lastVisitedRoom].name << "." << endl;
	usleep(shortDelay);

	heroCash -= numPizzas;

	roomList = roomListStorage;
	heroList = heroListStorage;


	styledPrint("The End", 0);
	styledPrint("Made by: Adam Gincel", 1);
	usleep(longDelay);


}

bool Dungeon::fight(uint room)
{

	
	//a lot of the magic will happen here.
	if (room > roomListSize)
		return false;

	uint i, j;

	//cout << "Getting strongest hero. \n";
	uint strongestHero = getStrongestHero();
	//cout << "Strongest hero: " << strongestHero << endl;

	Room& arena = roomList[room];
	Hero& currentHero = heroList[strongestHero];

	styledPrint(currentHero.name + " versus " + arena.protectorName + " in the " + arena.name, 0);
	usleep(longDelay);

	while (arena.protectorStrength > 0 && !allHeroesDead()) //while enemy is alive and we're all not dead
	{
		//enemy attack strongest player

		int temp = currentHero.health;

		for (i = 0; i < arena.protectorStrength; i++)
		{
			temp--;
			
			if (temp == 0)
				i = arena.protectorStrength;
		}

		cout << arena.protectorName << randomOffenseVerb() << currentHero.name << ", dealing " << arena.protectorStrength << " damage and reducing their HP to " << temp << "." << endl;
		usleep(shortDelay);

		for (i = 0; i < arena.protectorStrength; i++) //deal damage one point at a time, don't go past zero;
		{
			currentHero.health--;

			if (currentHero.health == 0)
				i = arena.protectorStrength; //get out of loop if health is 0
		}

		for (i = 0; i < currentHero.strength; i++) //decrement from monster's health the same way
		{
			arena.protectorStrength--;

			if (arena.protectorStrength == 0)
				i = currentHero.strength;
		}

		cout << currentHero.name << randomOffenseVerb() << arena.protectorName << ", dealing " << currentHero.strength << " damage and reducing their HP to " << arena.protectorStrength << "." << endl;
		usleep(shortDelay);



		if (currentHero.health == 0) //current hero is dead
		{
			cout << currentHero.name << " has fallen! " << endl;
			usleep(shortDelay * .75);

			currentHero.strength = 0;
			heroList[strongestHero] = currentHero;
			

			strongestHero = getStrongestHero();

			if (allHeroesDead())
				return false;

			currentHero = heroList[strongestHero];

			cout << currentHero.name << " has taken his place." << endl;
			usleep(shortDelay);
		}

		if (arena.protectorStrength == 0)
		{
			heroCash += arena.treasure;
			cout << endl << arena.protectorName << " has fallen! The heroes gained " << arena.treasure << " gold, and now have " << heroCash << " gold coins." << endl;
			usleep(shortDelay);

			heroList[strongestHero] = currentHero;

			return true;
		}

		

		cout << endl;
	}

	cout << "How did you end up here?\n";
	if (!allHeroesDead())
		return true;
	return false;


}

uint Dungeon::getStrongestHero()
{
	uint strongestHero = 0;
	for (uint i = 0; i < heroListSize; i++)
	{
		if (heroList[i].strength > heroList[strongestHero].strength && heroList[i].strength != INF && heroList[i].health > 0) //hero has greater strength, hero exists, hero isn't dead
			strongestHero = i;
	}

//	cout << "Strongest hero in progress: " << strongestHero << endl;

	if (heroList[strongestHero].health == 0 || heroList[strongestHero].strength == INF) //if hero is dead or doesn't exist
	{
		return INF;
	}

	return strongestHero;
}


bool Dungeon::allHeroesDead()
{
	bool result = true;

	for (uint i = 0; i < heroListSize; i++)
	{
		if (heroList[i].health > 0)
			result = false;
	}

	return result;
}

string Dungeon::randomOffenseVerb()
{
	int choice = rand() % 5;

	string ret = " ";

	switch (choice)
	{
	case 0:
		ret += "attacked";
		break;
	case 1:
		ret += "struck";
		break;
	case 2:
		ret += "assaulted";
		break;
	case 3:
		ret += "eviscerated";
		break;
	case 4:
		ret += "smashed";
		break;
	}

	ret += " ";

	return ret;

}