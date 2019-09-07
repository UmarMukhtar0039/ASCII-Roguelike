#pragma once
#include"Player.h"
#include<iostream>
#include<fstream>
#include<ostream>
#include<string>
#include<vector>
#include"Enemy.h"

using namespace std;

class Level
{
public:
	Level();
	void loadLevel(string fileName,Player &player);
	void movePlayer(char input, Player &player);
	void print(Player player);
	char getTile(int x,int y);
	void setTile(int x, int y, char tile);
	void updateEnemies(Player &player);
	
private:
	void battleMonster(Player &player, int targetX, int targetY);
	void processPlayerMove(Player &player,int targetX, int targetY);
	void processEnemyMove(Player &player,int enemyIndex, int targetX, int targetY);
	vector<string> _levelData;
	vector<Enemy> _enemies;

};

