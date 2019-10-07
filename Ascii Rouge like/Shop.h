#pragma once
#include"Items.h"
#include<vector>
#include "Entity.h"

class Shop : public Entity
{
public:
	Shop(std::string name, int money, std::vector<Items>);
	Shop() { _Smoney = 0; };
	~Shop();
	
	//Shop(Shop&& rhs)  ;
private:
	int _Smoney;
	std::vector<Items> _SInventory;
public:
	//void addItem(std::list<Items>& list);
	void printShop ()const;
	//const std::vector<Items>& getInventory()const ;
	std::vector<Items>::iterator Find(std::string& item);
	void sellItem(std::vector<Items>::iterator item);  // No need to take iterator by reference.
	std::vector<Items>::iterator returnItemEnd() { return _SInventory.end(); }
};

