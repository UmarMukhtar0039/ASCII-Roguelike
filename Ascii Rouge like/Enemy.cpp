#include "Enemy.h"
#include<random>
#include<ctime>
#include <string>


Enemy::Enemy(std::string name, char tile, int level, int attack, int defence, int health, int xp)
{
	_level = level;
	_name = name;
	_tile = tile;
	_attack = attack;
	_defence = defence;
	_health = health;
	_experienceValue = xp;

}

void Enemy::setposition(int x, int y)
{
	_x = x;
	_y = y;
}

void Enemy::getposition(int &x, int &y)
{
	x = _x;
	y = _y;
}



int Enemy::attack()
{
	static std::default_random_engine radomEngine(unsigned int(time(NULL)));
	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(radomEngine);
}

int Enemy::takeDamage(int attack)
{
	attack -= _defence;
	//check if attack does damage
	if (attack > 0)
	{
		_health -= attack;
		//to cheak if he died
		if (_health <= 0)
			return _experienceValue;
		
	}
	return 0;
}


char Enemy::getMove(int playerX,int playerY)
{
	static std::default_random_engine randomEngine(unsigned int(time(nullptr)));
	std::uniform_int_distribution<int> moveRoll(0,6);
	int distance;
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);
	distance = adx + ady;
	if (distance <= 5)
	{  //Moving along X axis
		if (adx > ady)
		{
			if (dx > 0)
				return 'a';
			else
				return'd';

		}
		else 
		{  //Moving along Y axis
			if (dy > 0)
				return 'w';
			else
				return 's';
		}

	}
	int randomMove = moveRoll(randomEngine);
	switch (randomMove)
	{
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
			return '.';
	
	}
}

void Enemy::printStats()const
{
	std::cout << "Fighting " << _name << "\nAttack Power:" << _attack 
		<< " Health:" << _health
		<< " Defence:" << _defence<<std::endl;
              
}
