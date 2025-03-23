#include "Service.h"

vector<Stock>& Service::getAllStocks()
{
	return repo.getAll();
}

void Service::removeStock(const string& id)
{
	repo.remove(id);
}
