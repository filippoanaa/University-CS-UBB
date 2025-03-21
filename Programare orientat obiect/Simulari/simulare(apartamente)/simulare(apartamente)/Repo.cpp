#include "Repo.h"
#include<fstream>
#include<sstream>
#include<algorithm>
using std::ifstream;
using std::ofstream;
void Repo::loadFromFile()
{
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw RepoException("Eroare la deschiderea fisierului");

	}
	string linie;
	while (getline(fin, linie)) {
		if (!linie.empty()) {
			string curent, strada;
			int cnt = 0, pret = 0, suprafata = 0;
			std::stringstream linestream(linie);
			while (getline(linestream, curent, ';'))
			{
				if (cnt == 0) strada = curent;
				if (cnt == 1) suprafata = stoi(curent);
				if (cnt == 2) pret = stoi(curent);
				cnt++;
			}
			Apartament ap{ strada,suprafata,pret };
			apartamente.push_back(ap);
		}
	}
	fin.close();
}

void Repo::saveToFile(vector<Apartament>& apartamente)
{
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw RepoException("Eroare la deschiderea fisierului");

	}
	for (auto& ap : apartamente) {
		fout << ap.getStrada() << ";" << ap.getSuprafata() << ";" << ap.getPret() << "\n";
	}
	fout.close();
}

vector<Apartament>& Repo::getAll()
{
	return apartamente;
}

void Repo::remove(const string& strada, int supraf, int pret)
{
	auto it = std::find_if(apartamente.begin(), apartamente.end(), [&](Apartament& ap) {
		return ap.getStrada() == strada && ap.getSuprafata() == supraf && ap.getPret() == pret;
		});
	if (it == apartamente.end()) {
		throw RepoException("Apartamentul nu exista!");
	}
	else
	{
		apartamente.erase(it);
		saveToFile(apartamente);
	}
}
