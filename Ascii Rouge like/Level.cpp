#include "Level.h"


Level::Level()
{
}

void Level::loadLevel(std::string fileName, Player &player)
{   // Loads the level
	std::ifstream file;
	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}
	std::string line;

	while (getline(file, line))
	{
		_levelData.emplace_back(line);
	}
	
	/*char ch;
	file>>ch;
	while (!file.eof())
	{
		cout << ch;
		file.get(ch);
	}*/
	//Process the level
	char tile;
	for (size_t i = 0; i < _levelData.size(); i++)
	{
		for (size_t j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];

			switch (tile)
			{
				{case '@':
					player.setposition((int)j, (int)i);
					break;
				}
				{case 'S'://Snake
					_enemies.push_back(Enemy("Snake", tile, 50, 5, 4, 10, 5));
					_enemies.back().setposition(static_cast<int>(j), static_cast<int>(i));
					break;
				}
				{case 'G'://Goblin
					_enemies.push_back(Enemy("Goblin", tile, 55, 10, 7, 10, 10));
					_enemies.back().setposition(static_cast<int>(j), static_cast<int>(i));
					break;
				}
				{case 'D'://Dragon
					_enemies.push_back(Enemy("Dragon", tile, 100, 100, 70, 80, 50));
					_enemies.back().setposition(static_cast<int>(j), static_cast<int>(i));
					break;
				}
				{case 'O'://Ogre
					_enemies.push_back(Enemy("Ogre", tile, 5, 25, 34, 43, 30));
					_enemies.back().setposition(int(j),int(i));
					break;
				}
				{case 'B'://Bandit
					_enemies.push_back(Enemy("Bandit", tile, 3, 40, 12, 120, 20));
					_enemies.back().setposition(int(j),int(i));
					break;
				}
				{case '^'://Chemist Shop
					std::vector<Items> chemistitems = { {"Health Potion",100,20},
														{"Attack Potion",240,40},
														{"Exp Potion", 200, 20} 
					};
					_shops.emplace_back(Shop("The Alchemist", 1000, chemistitems));
					_shops.back().setposition(int(j), int(i));
					break;
				}
				{case '~'://Food Shop
					std::vector<Items> fooditems = { {"Burger",100,20},
													 {"Pizza",50,120 },
													 {"Fish",30,400 }
					};
					_shops.emplace_back(Shop("Food Paradise", 1200, fooditems));
					_shops.back().setposition(int(j), int(i));
					break;
				}
				{case '<'://Weapon Shop
					std::vector<Items> weapons = { {"Silver Sword",100,200},
													{"Bronze Sword",50,120 },
													{"Iron Armor",30,400 }
					};
					_shops.emplace_back(Shop("Weapons Shop", 2000, weapons));
					_shops.back().setposition(int(j), int(i));
					break;
				}
			}
			


		}

	}

}

//using namespace std;
void Level::print(Player& player) const
{
	system("cls");
	player.printPlayer();

	for (size_t i = 0; i < _levelData.size(); i++)
	{
		std::cout << _levelData[i].c_str() << std::endl;
	}
	std::cout << std::endl;
	
}

void Level::movePlayer(char input, Player &player)
{
	int playerX;
	int playerY;
	player.getposition(playerX, playerY);
	switch (input)
	{
	case 'w'://up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 'a'://left
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 's'://down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'd'://right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	case 'q':
		player.healthPotion();
		break;
	case 'r':
		player.attackPotion();
	default:
		std::cout << " invalid input\n";
		system("PAUSE");
		break;
	}

}

char Level::getTile(int x, int y) const
{
	return _levelData[y][x];

}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;

}


void Level::processPlayerMove(Player &player, int targetX, int targetY)
{
	int playerX;
	int playerY;
	player.getposition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
		{case '#':
			std::cout << "You ran into a wall\n";
			system("PAUSE");
			break; }
		{case '.':
			player.setposition(targetX, targetY);
			setTile(playerX, playerY, '.');
			setTile(targetX, targetY, '@');
			break; }
		{case '^': // Chemist Shop
			auto it = getShop(_shops,"The Alchemist");
			shopEnter(player, *it);
			break;
		}
		{case '~': // Food Shop
			auto it = getShop(_shops, "Food Paradise");
			shopEnter(player, *it);
			break;
		}
		{case '<'://Weapon Shop
			auto it = getShop(_shops, "Weapons Shop");
			shopEnter(player, *it);
			break;
		}
		{default:
			battleMonster(player, targetX, targetY);
			break;
		}
	}
}

void Level::battleMonster(Player &player, int targetX, int targetY)
{   
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;
	std::string enemyName;
	
	player.getposition(playerX, playerY);
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getposition(enemyX,enemyY);
		enemyName = _enemies[i].getName();
		if (targetX == enemyX && targetY == enemyY)
		{
			//Battle
			attackRoll = player.attack();
			system("cls");
			print(player);
			_enemies[i].printStats();
			system("PAUSE");
			std::cout << "\nPlayer attacked monster "<<enemyName <<" with a roll of " << attackRoll<< std::endl;
			attackResult=_enemies[i].takeDamage(attackRoll);
			if (attackResult != 0)
			{
				setTile(targetX, targetY, '.');
				print(player);
				std::cout << "Monster died\n";
				auto it = _enemies.begin();
				it += i;
				_enemies.erase(it);
				
				i--;
				system("PAUSE");
				player.addExperience(attackResult);
				if (_enemies.size() == 0)
				{
					system("cls");
					std::cout << "\n\n\n\t\t\t\t\n\n\n\n\t\t\n\t\n\tYou Won ";
					system("PAUSE");
					exit(0);

				}
				return;
			}
			//Monster's turn
			attackRoll = _enemies[i].attack();
			std::cout << "\nMonster " << enemyName << "attacked you with a roll of "<<attackRoll<< std::endl;
			attackResult = player.takeDamage(attackRoll);
			if (attackResult != 0)
			{
				setTile(playerX, playerY, 'x');
				print(player);
				std::cout << "You died\n";
				system("PAUSE");
				exit(0);
			}
			system("PAUSE");
			return;
			
		}

	}
}


void Level::updateEnemies(Player &player)
{
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;
	
	player.getposition(playerX, playerY);
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		aiMove = _enemies[i].getMove(playerX,playerY);
		_enemies[i].getposition(enemyX, enemyY);
		switch (aiMove)
		{
		case 'w'://up
			processEnemyMove(player,i,enemyX , enemyY - 1);
			break;
		
		case 's'://down
			processEnemyMove(player,i, enemyX, enemyY + 1);
			break;
		case 'a'://left
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd'://right
			processEnemyMove(player,i, enemyX + 1, enemyY);
			break;

		}

	}

}


void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;
	_enemies[enemyIndex].getposition(enemyX,enemyY);
	player.getposition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case '.':
		_enemies[enemyIndex].setposition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY,_enemies[enemyIndex].getTile());
		break;
	case'@':
		battleMonster(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}



void Level::shopEnter(Player& player, Shop& shop)
{
	system("cls");
	std::cout << "\n\n";
	shop.printShop();
	char input ='a';
	while (input != 'q')
	{
		system("cls");
		player.printPlayer();
		shop.printShop();
		std::cout << "\n\nPress B/b to buy\nPress Q/q to quit\n";
		std::cin >> input;
		if (input == 'b' || input == 'B')
		{
			std::cin.ignore(1, '\n');
			std::string item;
			std::cout << "Enter Name of the item\n\n";
			std::getline(std::cin, item);
			auto it = shop.Find(item);
			if (it == _shops[getShopIndex(shop)].returnItemEnd())
			{
				return;
			}
			int itemcost = it->getvalue();
			if (player.canAfford(itemcost))

			{
				auto it = shop.Find(item);
				player.addItem(*it);
				shop.sellItem(it);
			}
			else
			{
				std::cout << "Too Expensive";
			}
		}
	}
}


std::vector<Shop>::iterator Level::getShop(std::vector<Shop>& shop, std::string shopName)const
{
	for (auto it = shop.begin(); it!=shop.end(); it++)
	{
		if (it->getName() == shopName)
			return it;
	}
}

int Level::getShopIndex(Shop& shop) const
{
	int i = 0;
	for (Shop s : _shops)
	{
		if (s.getName() == shop.getName())
			return i;
		i++;
	}
	return -1;
}



/*void Level::ShowLevel()
{
	ifstream fin;
	int i = 0, j = 0;
//	ifstream fin;
	fin.open("Level.txt");
	char **ch= new char*[15];
//	char ch;
//	fin.get(ch);
	
	for(;!fin.eof();)
	{  
		for(;;j++)
		  fin >> ch[i][j];
		i++;
	}
/*	while (!fin.eof())
	{
		cout << ch;
		ch = fin.get();
	}*/
	//fin.close();
//}