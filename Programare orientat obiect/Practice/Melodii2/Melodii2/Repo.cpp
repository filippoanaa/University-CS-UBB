#include "Repo.h"
#include<fstream>
#include<exception>
#include<sstream>
#include<qdebug.h>
using std::ifstream;
using std::ofstream;
using std::exception;

void Repo::loadFromFile()
{
	ifstream fin(filename);
	try{
		if (!fin.is_open())
			throw exception("Eroare la deschiderea fisierului!");
		string linie;
		while (getline(fin, linie)) {
			string curent, artist, titlu, gen;
			int id=0, cnt = 0;
			std::stringstream stream(linie);
			while (getline(stream, curent, ' ')) {
				if (cnt == 0) id = stoi(curent);
				if (cnt == 1) titlu = curent;
				if (cnt == 2) artist = curent;
				if (cnt == 3) gen = curent;
				cnt++;
			}
			Melodie m{ id,titlu,artist,gen };
			melodii.push_back(m);
		}
		fin.close();
	}
	catch (exception& e) {
		qDebug() << e.what();
	}

}

void Repo::saveToFile(vector<Melodie>& melodii)
{
	try {
		ofstream fout(filename);
		if (!fout.is_open()) {
			throw exception{ "Eroare la scrierea in fisieer" };
		}
		for (const auto& m : melodii) {
			fout << m.getId() << " " << m.getTitlu() << " " << m.getArtist() << " " << m.getGen() << "\n";
		}
	}
	catch (exception& e) {
		qDebug() << e.what();
	}
}

vector<Melodie>& Repo::getAll()
{
	return melodii;
}


void Repo::store(Melodie& m)
{
	melodii.push_back(m);
	saveToFile(getAll());
}

void Repo::remove(Melodie& m)
{
	auto it = std::find_if(melodii.begin(), melodii.end(), [&](const Melodie& melodie) {
		return m.getId() == melodie.getId();
		});
	if (it != melodii.end()) {
		melodii.erase(it);
		saveToFile(melodii);
	}
	else {
		throw exception("Nu exista melodie cu acest id!!");
	}
}
