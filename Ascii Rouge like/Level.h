#pragma once
#include<iostream>
#include<fstream>
#include<ostream>
#include<string>
#include<vector>

#include"Enemy.h"
#include"Player.h"
#include"Shop.h"

class Level
{
public:
	Level();
	void loadLevel(std::string fileName,Player &player);
	void movePlayer(char input, Player &player);
	void print(Player& player)const;
	char getTile(int x,int y)const;
	void setTile(int x, int y, char tile);
	void updateEnemies(Player &player);
	void shopEnter(Player&, Shop&);
	std::vector<Shop>::iterator getShop(std::vector<Shop>& shop, std::string shopName)const;
	int getShopIndex(Shop& shop)const;
	

private:
	void battleMonster(Player &player, int targetX, int targetY);
	void processPlayerMove(Player &player,int targetX, int targetY);
	void processEnemyMove(Player &player,int enemyIndex, int targetX, int targetY);
	std::vector<std::string> _levelData;
	std::vector<Enemy> _enemies;
	std::vector<Shop> _shops;
};

