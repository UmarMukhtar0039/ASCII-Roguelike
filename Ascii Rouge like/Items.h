#pragma once
#include<iostream>

class Items
{
public:
	Items(std::string&&, int, int);
	Items() :Items("none", 0, 0) {} // ctor delegation
	Items(Items&& rhs)noexcept : _ItemName(std::move(rhs._ItemName)),
		_ItemValue(rhs._ItemValue),_ItemCount(rhs._ItemCount){}
	Items(const Items& rhs): _ItemName(rhs._ItemName),
		_ItemValue(rhs._ItemValue), _ItemCount(rhs._ItemCount) {}
	Items& operator=(const Items& rhs)
	{
		_ItemName = rhs._ItemName;
		_ItemValue = rhs._ItemValue;
		_ItemCount = rhs._ItemCount;
		return *this;
	}
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

