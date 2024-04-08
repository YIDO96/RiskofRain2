#pragma once
class Inventory
{
private:
	int itemCount = 0;


public:
	map<string, int> itemList;

	Inventory();
	~Inventory();

	void AddItem(string name);

	map<string, int> GetItemList() { return itemList; }
};

