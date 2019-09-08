#include<iostream>
#include<string>

#include "Items.h"

Items::Items(std::string name, int value, int count)
	: _ItemName(name), _ItemValue(value), _ItemCount(count)
{
}


Items::~Items()
{
}

std::ostream& operator<<(std::ostream& stream, Items& item)
{
	return stream << item._ItemName << " X " << item._ItemCount
		<< "	     Cost: " << item._ItemValue << " Each\n";
}
