#include "GameSystem.h"
#include<conio.h>


GameSystem::GameSystem(std::string levelFile)
{
	std::string Pname;
	std::cout << "Enter Thy Name:";
	std::getline(std::cin,Pname);
	_player.init(Pname,3, 100, 70,10, 0,200);
	_level.loadLevel(levelFile,_player);
}



void GameSystem::PlayGame()
{
	bool isDone = false;
	while (isDone == false)
	{
		_level.print(_player);
		playerMove();
		_level.updateEnemies(_player);
		
	}

}

void GameSystem::playerMove()
{
	wint_t input;
	std::cout<<"Press q for Health Potions /t r for Attack Potions";
	std::cout << "\n Enter a move command(w/a/s/d):\n" ;
	input = _getwch();
	std::cout.flush();
	_level.movePlayer((char)input, _player);
	
}