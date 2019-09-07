#pragma once
#include<random>
#include<ctime>
#include<string>

using namespace std;

class Enemy
{
public:

		Enemy(string name, char tile, int level, int attack, int defence, int health, int xp);
		void setposition(int x, int y);
		void getposition(int &x, int &y);
		int attack();
		int takeDamage(int attack);
		string getName() { return _name; }
		char getTile() { return _tile; }
		//Get AI move command
		char getMove(int playerX, int playerY);
		


private:
	int _x, _y;
	string _name;
	char _tile;
	int _level;
	int _attack;
	int _defence;
	int _health;
	int _experienceValue;


};

