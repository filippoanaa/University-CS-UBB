#include "Repo.h"
#include<fstream>
#include <sstream>
#include <iostream>
using std::ifstream;
void Repo::loadFromFile()
{
	try {
		ifstream fin(filename);
		if (!fin.is_open()) {
			throw RepoException("Fisierul nu poate fi deschis");
		}
		string linie;
		while (getline(fin, linie))
		{
			if (linie != "") {
				string curent, numePl, numePr, socluPl, socluPr;
				int pretPr = 0, pretPl = 0, nrT = 0;
				std::stringstream linestream(linie);
				std::vector<string> componente;
				while (getline(linestream, curent, ',')) {
					componente.push_back(curent);
				}
				if (componente.size() == 3) {
					numePl = componente[0];
					socluPl = componente[1];
					pretPl = stoi(componente[2]);
					PlacaDeBaza pl(numePl, socluPl, pretPl);
					placi.push_back(pl);
				}
				if (componente.size() == 4) {
					numePr = componente[0];
					socluPr = componente[1];
					nrT = stoi(componente[2]);
					pretPr = stoi(componente[3]);
					Procesor pr(numePr, socluPr, nrT, pretPr);
					procesoare.push_back(pr);
				}

			}
		}
		fin.close();

	}
	catch (RepoException& e) {
		std::cout << e.getError();
	}


}

void Repo::store(PlacaDeBaza& pl)
{
	auto all = placi;
	auto it = std::find_if(placi.begin(), placi.end(), [&](PlacaDeBaza& p) {
		return pl.getNumePlaca() == pl.getNumePlaca() && pl.getSocluPlaca() == p.getSocluPlaca();
		});
	if (it != placi.end()) {
		throw RepoException("Placa exista deja!");
	}
	placi.push_back(pl);

}


vector<Procesor>& Repo::getProcesoare()
{
	return procesoare;
}

vector<PlacaDeBaza>& Repo::getPlaci()
{
	return placi;

}
