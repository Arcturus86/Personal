// PE7_Pointers_Start.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class MovableObject
{
public:
	int xPos;
	int yPos;
	void PrintPos()
	{
		cout << "X:" << xPos << " Y:" << yPos << endl;
	}
};

class Player : public MovableObject
{
public:
	char* name;
	Player()
	{
		cout << "player ctor" << endl;
		name = new char[15];
	}

	~Player()
	{
		cout << "player dtor" << endl;
		delete[] name;
	}
};

class Monster : public MovableObject
{
public:
	int damage;
};

int main()
{
	//Monster *boss = new Monster();
	//Player *pOne = new Player();
	MovableObject *boss = new Monster();

	//Since player was made using MovableObject instead of
	//Player, it will only call the Player method once,
	//indicated by the player ctor that gets printed.
	//When it gets deleted we are technically deleting
	//a MovableObject, not a Player.
	MovableObject *pOne = new Player();
	Monster *fakeMonster = (Monster*)pOne;


	// add code here
	//fakeMonster is sharing it's data with pOne, instead of each having their own data.
	//Since the data in pOne gets deleted before fakeMonster is deleted
	//it is basically deleting nothing, causing the error to occur
	cout << boss << endl;
	cout << pOne << endl;
	cout << fakeMonster << endl;

	boss->xPos = 45;
	boss->yPos = 21;
	pOne->xPos = 65;
	pOne->yPos = 76;
	fakeMonster->xPos = 82;
	fakeMonster->yPos = 32;

	boss->PrintPos();
	pOne->PrintPos();
	fakeMonster->PrintPos();

	delete boss;
	delete pOne;
	//delete fakeMonster;

	return 0;
}

