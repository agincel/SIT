#include "Dungeon.h"

#include <fstream>
#include <limits>

void testBipartiteOddEven(uint n, uint m)
{
	Dungeon d((n + m), 5);
	for (uint i = 0; i < (n + m); i++)
	{
		d.addRoom("aaaaah", "adam", i, 100);
	}
	for (uint j = 0; j < n; j++){
		for (uint k = n; k < (n + m); k++)
		{
			uint weight = ((j + 5) * 31 + (k + 5) * 37) % 233;
			if (weight % 2 == 0)
			{
				d.setHall(j, k, weight);
			}
			else{
				d.setHall(k, j, weight);
			}
		}
	}
	d.depthRooms();
	d.breadthRooms();
	d.mst();
}

int f(int n)
{
	int m, i, j, ret;
	if (n <= 0) {
		return 1;
	}
	m = n / 2;
	ret = 0;
	ret += f(m);
	for (i = 0; i < n; i++) {
		for (j = i; j > 0; j--) {
			ret += n;
		}
	}
	return ret;
}




int main()
{
	/*Dungeon* myDungeon = new Dungeon(); //my pacman testcase
	myDungeon->addRoom("Test Room 1", "Alex", 5, 15);
	myDungeon->addRoom("Test Room 2", "Mark", 4, 3);
	myDungeon->addRoom("Test Room 3", "Jeff", 7, 60);
	myDungeon->addRoom("Test Room 4", "Matt", 10, 10000);
	myDungeon->addRoom("Test Room 5", "James", 9, 120);

	myDungeon->setHall(0, 1, 5);
	myDungeon->setHall(1, 0, 6);
	myDungeon->setHall(1, 2, 6);
	myDungeon->setHall(2, 3, 9);
	myDungeon->setHall(0, 3, 10);
	myDungeon->setHall(0, 4, 11);*/
	

	/*myDungeon->setHall(0, 1, 22); //alex's halls maybe
	myDungeon->setHall(0, 2, 13);
	myDungeon->setHall(1, 2, 14);
	myDungeon->setHall(1, 3, 15);
	myDungeon->setHall(3, 4, 15);
	//myDungeon->setHall(2, 4, 100);*/

	/*
	Dungeon* myDungeon = new Dungeon(3, 6); //professor's example, 3 vertex cyclic complete graph

	myDungeon->addRoom("A", "Alex", 2, 4);
	myDungeon->addRoom("B", "Brian", 3, 2);
	myDungeon->addRoom("C", "Clyde", 1, 5);
	myDungeon->addRoom("D", "Derp", 50, 100);

	myDungeon->setHall(0, 1, 1);
	myDungeon->setHall(1, 0, 1);

	myDungeon->setHall(2, 0, 200);
	myDungeon->setHall(2, 1, 100);

	myDungeon->setHall(0, 3, 100);
	myDungeon->setHall(1, 3, 200);
	*/
	/*Dungeon* myDungeon = new Dungeon(5, 5);

	myDungeon->addRoom("A", "blah", 5, 15);
	myDungeon->addRoom("B", "blah", 4, 9);
	myDungeon->addRoom("C", "blah", 7, 60);
	myDungeon->addRoom("D", "blah", 10, 10000);
	myDungeon->addRoom("E", "blah", 9, 120);

	myDungeon->setHall(0, 1, 5);
	myDungeon->setHall(1, 0, 6);
	myDungeon->setHall(1, 2, 3);
	myDungeon->setHall(2, 3, 9);
	myDungeon->setHall(0, 3, 10);
	myDungeon->setHall(0, 4, 11);
	myDungeon->setHall(1, 3, 3);
	myDungeon->setHall(4, 3, 5);
	myDungeon->setHall(0, 2, 2);
	myDungeon->setHall(2, 1, 30);

	
	myDungeon->listRooms();
	myDungeon->showHalls();
	myDungeon->addHero("Dickshoe McGee", 420, 69);
	myDungeon->showHeroes();

	myDungeon->depthRooms();
	myDungeon->breadthRooms();

	myDungeon->mst();
	myDungeon->lucrativePath(0);
	myDungeon->lucrativePaths();

	cout << endl << endl;

	myDungeon->pizzaParty(0, 4, 250);


	//cin.get();*/

	//ifstream ifs("dungeon2.dat");
	ifstream ifs("C:\\Users\\Owner\\Documents\\0 - College Work\\1 - Freshman Year\\CS182\\Dungeon\\dungeon.dat");
	
	
	int numNodes;
	int numEdges;
	int numHeroes;

	if (!ifs)
		return 2;

	ifs >> numNodes;
	ifs >> numEdges;
	ifs >> numHeroes;

	Dungeon myDungeon = Dungeon(numNodes, numHeroes);

	uint i = 0;

	string roomID;
	string monsterName;
	uint strength;
	uint treasure;
	for (i = 0; i < numNodes; i++)
	{
		ifs >> roomID;
		ifs >> monsterName;
		ifs >> strength;
		ifs >> treasure;

		myDungeon.addRoom(roomID, monsterName, strength, treasure);
	}


	//Source Destination Capacity
	uint src;
	uint dst;
	uint capacity;
	for (i = 0; i < numEdges; i++)
	{
		ifs >> src;
		ifs >> dst;
		ifs >> capacity;

		myDungeon.setHall(src, dst, capacity);
	}

	//Name Strength Health
	string heroName;
	uint heroStrength;
	uint hp;
	for (i = 0; i < numHeroes; i++)
	{
		ifs >> heroName;
		//cout << heroName << endl;
		ifs >> heroStrength;
		//cout << heroStrength << endl;
		ifs >> hp;
		//cout << hp << endl;

		myDungeon.addHero(heroName, heroStrength, hp);
	}

	int input = 1;
	uint beginInput = 0;
	uint endInput = 0;
	uint moneyInput = 0;
	while (input != 0)
	{
		myDungeon.styledPrint("Main Menu", 0);
		cout << "1: Depth First Search" << endl;
		cout << "2: Breadth First Search" << endl;
		cout << "3: Hall List" << endl;
		cout << "4: Hero List" << endl;
		cout << "5: Maximum Pizza Spanning Tree" << endl;
		cout << "6: Lucrative Path" << endl;
		cout << "7: Lucrative Paths" << endl;
		cout << "8: Pizza Party!" << endl;
		cout << "9: Raid!" << endl;
		cout << "0: Exit" << endl;

		cout << endl;

		cout << "Choose an option: ";
		input = 0;
		while (!(cin >> input)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Choose an Option: \n";
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (input == 1)
			myDungeon.depthRooms();
		else if (input == 2)
			myDungeon.breadthRooms();
		else if (input == 3)
			myDungeon.showHalls();
		else if (input == 4)
			myDungeon.showHeroes();
		else if (input == 5)
			myDungeon.mst();
		else if (input == 6)
		{
			myDungeon.listRooms();

			cout << "What room index would you like to start from?" << endl;
			while (!(cin >> beginInput)) {
				cout << "Invalid input.\nWhat room index would you like to start from?\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			myDungeon.lucrativePath(beginInput);
		}
		else if (input == 7)
			myDungeon.lucrativePaths();
		else if (input == 8)
		{
			myDungeon.listRooms();

			//cout << "Hero budget: $" << myDungeon.heroCash << endl << endl;

			cout << "What room index would you like to start from?" << endl;
			while (!(cin >> beginInput)) {
				cout << "Invalid input.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "What room index would you like to target?" << endl;
			while (!(cin >> endInput)) {
				cout << "Invalid input.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "How much hypothetical money do the heroes have?" << endl;
			while (!(cin >> moneyInput)) {
				cout << "Invalid input.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			myDungeon.styledPrint("Pizza Party", 0);

			if (!(beginInput > myDungeon.roomListSize) && !(endInput > myDungeon.roomListSize) && !(myDungeon.roomList[beginInput].treasure == INF) && !(myDungeon.roomList[endInput].treasure == INF))
				cout << "Maximum pizzas carryable from Room " << beginInput << " to Room " << endInput << ": " << myDungeon.pizzaParty(beginInput, endInput, moneyInput) << endl << endl;
			else
				cout << "Invalid indices!\n\n";
		}
		else if (input == 9)
		{
			myDungeon.listRooms();

			cout << "What room index would you like to start from?" << endl;
			while (!(cin >> beginInput)) {
				cout << "Invalid input.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			myDungeon.raid(beginInput);
		}
	}

}