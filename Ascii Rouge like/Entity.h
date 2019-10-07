#pragma once
#include <iostream>

class Entity
{
protected:
	// position 
	int _x, _y;
	std::string _name;
public:
	Entity(std::string&& , int x = 0,int y = 0);
	void setposition(int x, int y);
	void getposition(int& x, int& y) const;
	std::string getName()const { return _name; }

};

