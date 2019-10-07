#include "Enemy.h"
#include <string>


Enemy::Enemy(std::string name, char tile, int level, int attack, int defence, int health, int xp)
	:Character(name,level,attack,defence,health,xp)
{
	//_level = level;
	_tile = tile;
	//_attack = attack;
	//_defence = defence;
	//_health = health;

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
