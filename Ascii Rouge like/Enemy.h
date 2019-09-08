#pragma once
#include<random>
#include<ctime>
#include<string>
#include<iostream>

class Enemy
{
public:

		Enemy(std::string name, char tile, int level, int attack, int defence, int health, int xp);
		void setposition(int x, int y);
		void getposition(int &x, int &y);
		int attack();
		int takeDamage(int attack);
		std::string getName() { return _name; }
		char getTile() { return _tile; }
		//Get AI move command
		char getMove(int playerX, int playerY);
		void printStats()const;


private:
	int _x, _y;
	std::string _name;
	char _tile;
	int _level;
	int _attack;
	int _defence;
	int _health;
	int _experienceValue;


};

