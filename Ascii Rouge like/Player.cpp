#include "Player.h"
#include <random>
#include<ctime>
#include<iostream>

Player::Player()
{
	_x = 0;
	_y = 0;
	_level = 1;
	_health = 0;
	_attack = 0;
	_defence = 0;
	_experience = 0;
}

void Player::init(int level, int health, int attack, int defence, int experience)
{
	_level = level;
	_health = health;
	_attack = attack;
	_defence = defence;
	_experience = experience;
}


void Player::setposition(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::getposition(int &x, int &y) 
{
	x = _x;
	y = _y;
}


int Player::attack()
{
	static default_random_engine radomEngine(unsigned int(time(NULL)));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(radomEngine);
}


void Player::addExperience(int experience)
{
	_experience += experience;
	//Level up
	while (_experience > 20)
	{
		cout << "\nLeveled Up";
		_experience -= 20;
		_attack += 10;
		_defence += 5;
		_health += 10;
		_level++;
		system("PAUSE");
	}

}

int Player::takeDamage(int attack)
{
	attack -= _defence;
	//check if attack does damage
	if (attack > 0)
	{
		_health -= attack;
		if (_health <= 0)
			return 1;
		//to cheak if he died
	}
	return 0;
}
