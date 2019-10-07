#include "Entity.h"



Entity::Entity(std::string&& name,int x,int y)
	:_name(std::move(name)),_x(x),_y(y)
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
