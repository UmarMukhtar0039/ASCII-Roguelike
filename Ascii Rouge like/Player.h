#pragma once
#include<string>

using namespace std;

class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defence, int experience);
	void setposition(int x, int y);
	void getposition(int &x, int &y);
	int attack();
    void addExperience(int experience);
	int takeDamage(int attack);
	int _health;
	int _level;
	int _attack, _defence, _experience;
private:
	
	
	// position 
	int _x, _y;
};