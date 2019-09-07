#include "GameSystem.h"
#include<conio.h>


GameSystem::GameSystem(string levelFile)
{
	_player.init(3, 100, 2240,10, 0);
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
	cout << "\n Enter a move command(w/a/s/d): ";
	input = _getwch();
	_level.movePlayer((char)input, _player);
	
}