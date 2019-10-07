#pragma once
#include "Entity.h"

class Character :
	public Entity
{
protected:
	int _health;
	int _level;
	int _attack, _defence;
	int _experience;

public:
	Character(std::string name, int level, int attack, int defence, int health, int xp);
	int attack();
	int takeDamage(int attack);

};

