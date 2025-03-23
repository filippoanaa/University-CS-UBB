#include "Service.h"
#include<set>
vector<Tractor>& Service::getAllTractoare()
{
	return repo.getTractoare();
}

void Service::adaugaTractor(int id, string denumire, string tip, int roti)
{
	Tractor t{ id,denumire, tip, roti };
	val.valideaza(t);
	repo.add(t);
	
}

vector<string> Service::tipuriDistincte()
{
    vector<string> tipuri;
    const auto& tractoare = getAllTractoare(); 
    for (const auto& tr : tractoare) {
        if (std::find(tipuri.begin(), tipuri.end(), tr.getTip()) == tipuri.end()) {
            tipuri.push_back(tr.getTip());
        }
    }
    return tipuri;
}

void Service::updateNrRoti(int id)
{
    repo.update(id);
}

