#include <random>
#include<ctime>
#include<iostream>

#include "Player.h"

Player::Player()
{
	_x = 0;
	_y = 0;
	_level = 1;
	_health = 0;
	_attack = 0;
	_defence = 0;
	_experience = 0;
	_money = 200;
}

void Player::init(std::string name,int level, int health, int attack, int defence, int experience,int money)
{
	_name = name;
	_level = level;
	_health = health;
	_attack = attack;
	_defence = defence;
	_experience = experience;
	_money = money;
	playerinventory.emplace_back(Items("Bronze Sword",20, 1));
}


void Player::setposition(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::getposition(int &x, int &y) const
{
	x = _x;
	y = _y;
}


int Player::attack()
{
	static std::default_random_engine radomEngine(unsigned int(time(NULL)));
	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(radomEngine);
}


void Player::addExperience(int experience)
{
	_experience += experience;
	//Level up
	while (_experience > 20)
	{
		std::cout << "\n\n**Leveled Up**";
		_experience -= 20;
		_attack += 10;
		_defence += 5;
		_health += 10;
		_level++;
		std::cout<< std::endl;
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

void Player::printPlayer()
{
	std::cout << "\t\t\t\t\t\t*******Player Stats*********\n " 
		<< _name << "'s Inventory:\n";
	for (Items i : playerinventory)
		{
			std::cout << i;
		}
	std::cout << " health :" << _health << "\t\tlevel :" << _level << "\t\tAttack :" << _attack
		<< "\t Defence :" << _defence << "\tExperience :" << _experience 
		<< " Money:"<<_money<< std::endl;

		
}




bool Player::canAfford(int cost)
{
	if (cost > _money)
		return false;

	return true;
}

void Player::addItem(Items item)
{

	std::vector<Items>::iterator lit;
	for (lit = playerinventory.begin(); lit != playerinventory.end(); lit++)
	{
		if ((*lit).getItem() == item.getItem())
		{
			lit->addone();
			_money -= item.getvalue();
			return;
		}
	}
	item.setcount(1);
	playerinventory.emplace_back(item);
	_money -= item.getvalue();

}

void Player::healthPotion()
{
	for (Items i : playerinventory)
	{
		if (i.getItem() == "Health Potion")
		{	
			addHealth();
			i.setcount(i.getcount()-1) ;		
			return;
		}
	}
	std::cout << "No Health Potion\n";
	wint_t input;
	input = _getwch();
	std::cout.flush();
}

void Player::attackPotion()
{
	for (Items i : playerinventory)
	{
		if (i.getItem() == "Attack Potion")
		{
			_attack += 20;
			i.setcount(i.getcount() - 1);
			return;
		}
	}
	std::cout << "No Attack Potion\n";
	wint_t input;
	input = _getwch();
	std::cout.flush();
}


void Player::addHealth()
{
	if (_health < 70)
	{
		_health += 20;
	}
	else
		std::cout << "Health is enough";
}