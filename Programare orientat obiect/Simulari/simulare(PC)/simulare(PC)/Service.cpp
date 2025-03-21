#include "Service.h"
#include<algorithm>
#include<functional>
#include <iterator>
#include <iostream>
vector<Procesor>& Service::getProcesoare()
{
	return repo.getProcesoare();
}

vector<PlacaDeBaza>& Service::getPlaci()
{
	return repo.getPlaci();

}

void Service::adaugaPlaca(const string& nume, const string& procesor, int pret)
{
	PlacaDeBaza pl{ nume, procesor,pret };
	repo.store(pl);
}

vector<PlacaDeBaza> Service::filtrare(const string& soclu)
{
	vector<PlacaDeBaza> all = getPlaci();
	vector<PlacaDeBaza> filtrate;
	std::copy_if(all.begin(), all.end(), back_inserter(filtrate), [&](PlacaDeBaza& p) {

		return p.getSocluPlaca() == soclu;
		});
	return filtrate;

}
PlacaDeBaza Service::findPlaca(string& nume)
{
	for (const auto& pl : getPlaci()) {
		if (pl.getNumePlaca() == nume)
			return pl;
	}
}

Procesor Service::findProcesor(string& nume)
{
	for (const auto& pr : getProcesoare()) {
		if (pr.getNumeProcesor() == nume)
			return pr;
	}
}