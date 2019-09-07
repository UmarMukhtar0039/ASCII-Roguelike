#include<iostream>

#include"GameSystem.h"
#include"Level.h"

using namespace std;

int main()
{
	GameSystem gamesystem("LEVEL.txt");

	gamesystem.PlayGame();
//	cout << typeid(l1).name();
	system("PAUSE");

}


