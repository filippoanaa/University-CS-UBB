#include "Service.h"

vector<Apartament>& Service::getAllAp()
{
	return repo.getAll();
}

vector<Apartament> Service::filtrare(int min, int max)
{
	vector<Apartament> apartamente = getAllAp();
	vector<Apartament> filtrare;
	for (const auto& ap : apartamente) {
		if (ap.getSuprafata() > min && ap.getSuprafata() < max) {
			filtrare.push_back(ap);
		}
	}
	return filtrare;
}

vector<Apartament> Service::filtrarePret(int min, int max)
{
	vector<Apartament> apartamente = getAllAp();
	vector<Apartament> filtrare;
	for (const auto& ap : apartamente) {
		if (ap.getPret() > min && ap.getPret() < max) {
			filtrare.push_back(ap);
		}
	}
	return filtrare;
}

void Service::deleteAp(const string& strada, int supraf, int pret)
{
	repo.remove(strada, supraf, pret);
}
