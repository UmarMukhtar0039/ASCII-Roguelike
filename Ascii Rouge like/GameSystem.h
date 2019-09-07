#pragma once
#include"Player.h"
#include"Level.h"



class GameSystem
{
public:
	GameSystem(string levelFile);
	void playerMove();
	void PlayGame();

private:
	Level _level;
	Player _player;
	
};

