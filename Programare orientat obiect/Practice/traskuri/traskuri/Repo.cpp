#include "Repo.h"
#include<fstream>
#include<sstream>
using std::ifstream;
using std::ofstream;
void Repo::loadFromFile()
{
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw RepoException("Fisiserul nu a putut fi deschis!");
	}
	string linie;
	while (getline(fin, linie)) {
		if (!linie.empty()) {
			string curent, desc, stare;
			int id = 0, cnt = 0;
			vector<string> lst;
			std::stringstream stream1(linie);
			while (getline(stream1, curent, ';')) {
				if (cnt == 0) { id = stoi(curent); }
				if (cnt == 1) { desc = curent; }
				if (cnt == 2) {
					std::stringstream stream2(curent);
					string v;
					while (getline(stream2, v, ' ')) {
						lst.push_back(v);
					}
				}
				if (cnt == 3) { stare = curent; }
				cnt++;
			}
			Task t{ id,desc,lst,stare };
			tasks.push_back(t);
		}
	}
	fin.close();

}

void Repo::saveToFile()
{
	ofstream fout(filename);
	if (!fout.is_open())
		throw RepoException("Eroare la deschiderea fisierului!");
	for (auto& t : getAll()) {
		fout << t.getId() << ";" << t.getDesc() << ";";
		for (auto pr : t.getProgramatori())
			fout << pr << " ";
		fout << ";" << t.getStare() << "\n";
	}
	fout.close();

}

vector<Task>& Repo::getAll()
{
	return tasks;
}

bool Repo::exist(Task& task)
{
	for (const auto& t : tasks) {
		if (t.getId() == task.getId())
			return true;
	}
	return false;
}

void Repo::store(Task& t)
{
	if (exist(t))
		throw RepoException("Exista deja task cu acest id!");
	else
		tasks.push_back(t);
	saveToFile();
}
