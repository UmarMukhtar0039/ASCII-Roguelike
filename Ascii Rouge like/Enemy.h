#pragma once
#include<random>
#include<ctime>
#include<string>
#include<iostream>
#include "Character.h"

class Enemy : public Character
{
public:

		Enemy(std::string name, char tile, int level, int attack, int defence, int health, int xp);
		char getTile()const { return _tile; }
		//Get AI move command
		char getMove(int playerX, int playerY);
		void printStats()const;


private:
	char _tile;


};

