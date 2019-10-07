#include "Shop.h"
#include<iostream>


Shop::Shop(std::string name, int money, std::vector<Items> list)
	:_Smoney(money), _SInventory(list)
{
	_name = name;
}


Shop::~Shop()
{

}


void Shop::printShop()const 
{
	std::cout <<"\nWelcome to "<< _name << "\n\nItems Available:\n";
	for (Items i : _SInventory)
		std::cout << i ;
}


 std::vector<Items>::iterator Shop::Find(std::string& item) 
{
	auto it = _SInventory.begin();
	for (; it != _SInventory.end(); it++)
	{
		if (it->getItem() == item)
			return it;
	}
	std::cout << "We don't sell such item\nGet Out!\n";
	system("PAUSE");
	return _SInventory.end();
}

void Shop::sellItem(std::vector<Items>::iterator item)
{
	int count = item->getcount() - 1;
	item->setcount(count);
	_Smoney += item->getvalue();
	if (count == 0)
	{
		_SInventory.erase(item);
	}
}
