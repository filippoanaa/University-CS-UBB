#pragma once
#include<Repo.h>
class Service
{
private:
	Repo& repo;

public:
	Service(Repo& re) :repo{ re } {};
	Service(Service& ot) = delete;
	vector<Procesor>& getProcesoare();
	vector<PlacaDeBaza>& getPlaci();
	void adaugaPlaca(const string& nume, const string& procesor, int pret);
	vector<PlacaDeBaza> filtrare(const string& soclu);
	PlacaDeBaza findPlaca(string& nume);
	Procesor findProcesor(string& nume);
};

