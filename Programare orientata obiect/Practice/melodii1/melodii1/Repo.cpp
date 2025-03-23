#include "Repo.h"
#include<fstream>
#include<exception>
#include <qdebug.h>
#include<sstream>
#include<Melodie.h>
using std::ifstream;
using std::ofstream;
using std::exception;
void Repo::loadFromFile()
{
	try {
		ifstream fin(filename);
		if (!fin.is_open()) {
			throw exception("Nu a putut fi deschis fisierul ");
		}
		string line;
		while (getline(fin, line)) {
			if (!line.empty()) {
				int cnt = 0, id = 0, rank = 0;
				string curent, titlu, artist;
				std::stringstream linestream(line);
				while (getline(linestream, curent, ' ')) {
					if (cnt == 0) id = stoi(curent);
					if (cnt == 1) titlu = curent;
					if (cnt == 2) artist = curent;
					if (cnt == 3) rank = stoi(curent);
					cnt++;
				}
				Melodie m{ id,titlu,artist,rank };
				melodii.push_back(m);
			}
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
			throw exception("Eroare la scrierea in fisier!");
		}
		for (auto& m : melodii) {
			fout << m.getId() << " " << m.getTitlu() << " " << m.getArtist() << " " << m.getRank() << " " << "\n";
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

void Repo::update(Melodie& m, string titluNou, int rankNou)
{
	m.setRank(rankNou);
	m.setTitlu(titluNou);
	saveToFile(getAll());
}

void Repo::remove(int id)
{
	auto it = std::find_if(melodii.begin(), melodii.end(), [&](Melodie& m) {
		return m.getId() == id;
		});
	melodii.erase(it);
	saveToFile(getAll());
}
