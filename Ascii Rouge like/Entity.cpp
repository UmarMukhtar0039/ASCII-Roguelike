#include "Entity.h"





Entity::Entity()
	:_x(0),_y(0),_name("none")
{
}

void Entity::setposition(int x, int y)
{
	_x = x;
	_y = y;
}

void Entity::getposition(int& x, int& y) const
{
	x = _x;
	y = _y;
}
