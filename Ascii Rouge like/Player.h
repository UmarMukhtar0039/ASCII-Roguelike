#pragma once
#include<iostream>
#include<vector>
#include"Items.h"

class Player
{
public:
	Player();
	void init(std::string,int level, int health, int attack, int defence, int experience,int money);
	void setposition(int x, int y);
	void getposition(int &x, int &y) const;
	int attack();
    void addExperience(int experience);
	int takeDamage(int attack);
	void printPlayer();
	bool canAfford(int cost);
	void addItem(Items item);
	void healthPotion();
	void attackPotion();
private:
	void addHealth();
	std::string _name;
	std::vector<Items> playerinventory;
	int _health;
	int _level;
	int _attack, _defence, _experience;	
	int _money;
	// position 
	int _x, _y;
};