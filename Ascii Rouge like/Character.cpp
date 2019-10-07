#include "Character.h"
#include<random>
#include<ctime>


Character::Character(std::string&& name, int level, int attack, int defence, int health, int xp)
	: Entity(std::move( name),0,0),
	_level(level),_attack(attack),_defence(defence),_health(health),_experience(xp)
{
}

int Character::attack()
{
	static std::default_random_engine radomEngine(unsigned int(time(NULL)));
	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(radomEngine);
}

int Character::takeDamage(int attack)
{
	attack -= _defence;
	//check if attack does damage
	if (attack > 0)
	{
		_health -= attack;
		//to cheak if he died
		if (_health <= 0)
			return _experience;

	}
	return 0;
}
