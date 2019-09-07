#include "Level.h"

using namespace std;



Level::Level()
{
}

void Level::loadLevel(string fileName, Player &player)
{   // Loads the level
	ifstream file;
	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}
	string line;

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

			switch(tile)
			{
			case '@':
				player.setposition(j,i);
				break;
			
			case 'S'://Snake
				_enemies.push_back(Enemy("Snake", tile, 50, 5,4,10,5 ));
				_enemies.back().setposition(j, i);
				break;
			case 'G'://Goblin
				_enemies.push_back(Enemy("Goblin", tile,55, 10,7, 10,10));
				_enemies.back().setposition(j, i);
				break;
			case 'D'://Dragon
				_enemies.push_back(Enemy("Dragon", tile, 100, 100, 70, 80, 50));
				_enemies.back().setposition(j, i);
				break;
			case 'O'://Ogre
				_enemies.push_back(Enemy("Ogre", tile, 5, 25, 34, 43, 30));
				_enemies.back().setposition(j, i);
				break;
			case 'B'://Bandit
				_enemies.push_back(Enemy("Bandit", tile, 3, 40, 12, 120, 20));
				_enemies.back().setposition(j, i);
				break;
			}


		}

	}

}

//using namespace std;
void Level::print(Player player)
{
	system("cls");
	cout << "\t\t\t\t\t\t*******Player Stats*********\n health :"<<player._health<<"\t\tlevel :"
		<<player._level<<"\t\tAttack :" << player._attack<<"\t\t Defence :"
		<< player._defence<< "\t\tExperience :"<<player._experience<<endl  ;

	for (size_t i = 0; i < _levelData.size(); i++)
	{
		cout << _levelData[i].c_str() << endl;
	}
	 cout << endl;
	
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

	default:
		cout << " invalid input\n";
		system("PAUSE");
		break;
	}

}
char Level::getTile(int x, int y)
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
	case '#':
		cout << "You ran into a wall\n";
		system("PAUSE");
		break;
	case '.':
		player.setposition(targetX,targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	/*case '#':
		cout << "you ran into a wall";
		break;*/
	default:
		battleMonster(player,targetX,targetY);
		break;
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
	string enemyName;
	
	player.getposition(playerX, playerY);
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getposition(enemyX,enemyY);
		enemyName = _enemies[i].getName();
		if (targetX == enemyX && targetY == enemyY)
		{
			//Battle
			attackRoll = player.attack();
			cout << "\nPlayer attacked monster "<<enemyName <<" with a roll of " << attackRoll<<endl;
			attackResult=_enemies[i].takeDamage(attackRoll);
			if (attackResult != 0)
			{
				setTile(targetX, targetY, '.');
				print(player);
				cout << "Monster died\n";
				auto it = _enemies.begin();
				it += i;
				_enemies.erase(it);
				
				i--;
				system("PAUSE");
				player.addExperience(attackResult);
				if (_enemies.size() == 0)
				{
					system("cls");
					cout << "\n\n\n\t\t\t\t\n\n\n\n\t\t\n\t\n\tYou Won ";
					system("PAUSE");
					exit(0);

				}
				return;
			}
			//Monster's turn
			attackRoll = _enemies[i].attack();
			cout << "\nMonster " << enemyName << "attacked you with a roll of "<<attackRoll<<endl;
			attackResult = player.takeDamage(attackRoll);
			if (attackResult != 0)
			{
				setTile(playerX, playerY, 'x');
				print(player);
				cout << "You died\n";
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