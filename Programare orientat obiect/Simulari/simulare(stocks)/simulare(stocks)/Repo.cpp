#include "Repo.h"
#include<fstream>
#include<sstream>
using std::ifstream;
using std::ofstream;
#include<algorithm>
void Repo::loadFromFile()
{
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw RepoException("Fisierul nu a putut fi deschis");

	}
	string linie;
	while (getline(fin, linie)) {
		string id, nume, curent;
		float pret = 0.0;
		int mc = 0, cnt = 0;
		std::stringstream linestream(linie);
		while (getline(linestream, curent, ',')) {
			if (cnt == 0) id = curent;
			if (cnt == 1) nume = curent;
			if (cnt == 2) pret = stof(curent);
			if (cnt == 3) mc = stoi(curent);
			cnt++;
		}
		Stock s{ id, nume,pret,mc };
		stocks.push_back(s);
	}
	fin.close();

}

void Repo::saveToFile(vector<Stock>& stocks)
{
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw RepoException("Nu s a putut scrie in fisier");
	}
	for (auto& s : stocks) {
		fout << s.getId() << "," << s.getNume() << "," << s.getPret() << "," << s.getMChange() << "\n";
	}
	fout.close();
}

vector<Stock>& Repo::getAll()
{
	return stocks;
}

void Repo::remove(const string& id)
{
	auto it = std::find_if(stocks.begin(), stocks.end(), [&](Stock& s) {
		return id == s.getId();
		});
	stocks.erase(it);
	saveToFile(stocks);
}

