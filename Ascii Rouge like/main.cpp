#include<iostream>

#include"GameSystem.h"
#include"Level.h"


int main()
{
	std::string Pname;
	std::cout << "Enter Thy Name:";
	std::getline(std::cin, Pname);
	GameSystem gamesystem("LEVEL.txt",std::move(Pname));

	gamesystem.PlayGame();
//	cout << typeid(l1).name();
	system("PAUSE");

}


