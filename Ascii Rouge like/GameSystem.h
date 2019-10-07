#pragma once
#include"Player.h"
#include"Level.h"



class GameSystem
{
public:
	GameSystem(std::string&& levelFile,std::string&&);
	void playerMove();
	void PlayGame();

private:
	Level _level;
	Player _player;
	
};

