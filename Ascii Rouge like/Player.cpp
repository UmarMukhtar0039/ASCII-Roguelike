#include <random>
#include<ctime>
#include<iostream>

#include "Player.h"

Player::Player(std::string name, int level, int health, int attack, int defence, int experience, int money)
	:Character(name,level, attack,defence,health,experience)
{
	_money = 200;
	Items item("Bronze Sword", 20, 1);
	playerinventory.emplace_back(std::move(item));
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

void Player::printPlayer()
{
	std::cout << "\t\t\t\t\t\t*******Player Stats*********\n " 
		<< _name << "'s Inventory:\n";
	for (Items& i : playerinventory)
		{
			std::cout << i;
		}
	std::cout << " health :" << _health << "\t\tlevel :" << _level << "\t\tAttack :" << _attack
		<< "\t Defence :" << _defence << "\tExperience :" << _experience 
		<< " Money:"<<_money<< std::endl;

		
}




bool Player::canAfford(int cost) const
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
	for (Items& i : playerinventory)
	{
		if (i.getItem() == "Health Potion" && i.getcount() > 0)
		{	
			if (_health < 70) {
				_health += 20;
				i.setcount(i.getcount() - 1);
				return;
			}
		}
	}
	//std::cout << "No Health Potion\n";
	//wint_t input;
	//input = _getwch();
	std::cout.flush();
}

void Player::attackPotion()
{
	for (Items& i : playerinventory)
	{
		if (i.getItem() == "Attack Potion" && i.getcount() > 0)
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
