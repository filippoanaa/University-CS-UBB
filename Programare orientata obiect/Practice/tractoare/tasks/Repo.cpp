#include "Repo.h"
#include<fstream>
#include <sstream>
#include<qDebug>
using std::ifstream;
using std::ofstream;
using std::stringstream;
void Repo::loadFromFile()
{
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw RepoExceptions("Fisierul" + filename + "nu a putut fi deschis");
	}
	string linie;
	while (getline(fin, linie)) {
		if (!linie.empty()) {
			string curent, denumire, tip;
			int cnt = 0, nrRoti = 0, id = 0;
			std::stringstream linestream(linie);
			while (getline(linestream, curent, ',')) {
				if (cnt == 0) id = stoi(curent);
				if (cnt == 1)  denumire = curent;
				if (cnt == 2) tip = curent;
				if (cnt == 3) nrRoti = stoi(curent);
				cnt++;
			}
			Tractor t(id, denumire, tip, nrRoti);
			tractoare.push_back(t);
		}
	}
	fin.close();

}

void Repo::saveToFile()
{
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw RepoExceptions("Nu s a putut scrie in fisierul "+filename);
	}
	for (const auto& tr : tractoare) {
		fout << tr.getId() << "," << tr.getDenumire() << "," << tr.getTip() << "," << tr.getNrRoti() << "\n";
	}
	fout.close();

}

vector<Tractor>& Repo::getTractoare()
{
	return tractoare;
}

bool Repo::exista(int id)
{
	for (const auto& tr : tractoare) {
		if (tr.getId() == id) {
			return true;
		}
	}
	return false;

}

void Repo::add(const Tractor& tr)
{
	if (exista(tr.getId()))
		throw RepoExceptions("Tractorul cu acest id exista deja");
	else
		tractoare.push_back(tr);
	saveToFile();
}


Tractor& Repo::findTractor(int id)
{
	for (auto& tr : tractoare) {
		if (tr.getId() == id)
			return tr;
	}
	throw RepoExceptions("Tractorul cu acest id nu exista");
}


void Repo::update(int id) {
	Tractor& tr = findTractor(id);
	//qDebug() << "Număr de roți înainte de decrementare: " << tr.getNrRoti();
	tr.decrementNrRoti();
	//qDebug() << "Număr de roți după decrementare: " << tr.getNrRoti();
	saveToFile();
}
