#pragma once
#include<iostream>

class Items
{
public:
	Items(std::string, int, int);
	Items() { _ItemName = "none"; _ItemCount = 0; _ItemValue = 0; };
	~Items();
private:
	std::string _ItemName;
	int _ItemValue;
	int _ItemCount;

public:
	const std::string& getItem()const { return _ItemName; }
	int getvalue()const { return _ItemValue; }
	int getcount()const { return _ItemCount; }
	friend std::ostream& operator<<(std::ostream& stream, Items&);
	void setcount(int count) { _ItemCount = count; }
	void addone() { ++_ItemCount; }
};

