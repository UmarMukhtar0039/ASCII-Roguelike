#pragma once
#include"Items.h"
#include<vector>

class Shop
{
public:
	Shop(std::string name, int money, std::vector<Items>&);
	Shop() { _Sname = "none"; _Smoney = 0; };
	~Shop();
private:
	std::string _Sname;
	int _Smoney;
	std::vector<Items> _SInventory;
	int _x, _y;
public:
	//void addItem(std::list<Items>& list);
	void printShop ()const;
	const std::string& getName()const { return _Sname; }
	//const std::vector<Items>& getInventory()const ;
	std::vector<Items>::iterator Find(std::string& item);
	void sellItem(std::vector<Items>::iterator item);  // No need to take iterator by reference.
	void setposition(int x, int y);
	void getposition(int& x, int& y);
	std::vector<Items>::iterator returnItemEnd() { return _SInventory.end(); }
};

