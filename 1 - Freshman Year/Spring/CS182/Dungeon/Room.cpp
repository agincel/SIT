#include "Dungeon.h"

/*
Adam Gincel
Room.cpp
This contains methods pertaining to Rooms, which are private data members of Dungeons.

I pledge my honor that I have abided by the Stevens Honor System.
*/


/**
addRoom(string name, string protectorName, uint strength, uint treasure)
A public method that lets a user add a room (so long as there is room to fit one) within the roomList.

Input: string name, string protectorName, uint strength, uint treasure

Returns: int, the index of the room added.
*/
int Dungeon::addRoom(string name, string protectorName, uint strength, uint treasure)
{
	if (strength == INF || treasure == INF) //error checking
		return -1;

	for (uint i = 0; i < roomListSize; i++)
	{
		if (roomList[i].treasure == INF)
		{
			roomList[i] = Room(name, protectorName, strength, treasure);
			return i;
		}
	}

	return -1;
}



/**
listRooms()
A public method that lists all of the rooms in the roomList.

Input: None.

Returns: void, though prints a list of the rooms in roomList.
*/
void Dungeon::listRooms()
{
	styledPrint("Room List", 0);
	for (uint i = 0; i < roomListSize; i++)
	{
		if (roomList[i].treasure != INF)
		{
			cout << i << ": " << endl;
			cout << "\tName: " << roomList[i].name << endl;
			cout << "\tProtector Name: " << roomList[i].protectorName << endl;
			cout << "\tProtector Strength: " << roomList[i].protectorStrength << endl;
			cout << "\tTreasure: " << roomList[i].treasure << endl;
			cout << endl;
		}
	}

	cout << endl;

}

/**
printRoom()
A private method that prints a specific room on one line. Used to easily change the output of rooms later.

Input: uint s: the room being printed.

Returns: void, though prints out a room's information.
*/
void Dungeon::printRoom(uint s)
{
	if (!(s > roomListSize))
		cout << s << ": Name: " << roomList[s].name << " Protector Name: " << roomList[s].protectorName << " Protector Strength: " << roomList[s].protectorStrength << " Treasure: " << roomList[s].treasure << endl;
}