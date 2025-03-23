#pragma once
#include<Repo.h>
class Service
{
private:
	Repo& repo;
public:
	Service(Repo& repo) : repo{ repo } {};
	vector<Stock>& getAllStocks();
	void removeStock(const string& id);
};

