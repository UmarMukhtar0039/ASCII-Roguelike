#pragma once
#include<iostream>
#include<vector>
#include "Character.h"
#include"Items.h"

class Player : public Character
{
public:
    Player(std::string&& name, int level, int health, int attack, int defence, int experience, int money);
    void addExperience(int experience);
    void printPlayer();
    bool canAfford(int cost)const;
    void addItem(Items item);
    void healthPotion();
    void attackPotion();
	void EquipSword();
	void UnEquipSword();
	bool searchInventory(const std::string& ItemName);
	static bool swordisequip ;
private:
    std::vector<Items> playerinventory;
	int _money;
};

