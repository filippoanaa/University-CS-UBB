#include "repo.h"
#include<fstream>
#include<sstream>
#include<iostream>
using std::ifstream;
void Repo::loadFromFile()
{
	try {
		ifstream fin(filename);
		if (!fin.is_open()) {
			throw RepoException("Fisierul " + filename + " nu poatr fi decshis!");
		}
		string linie;
		while (getline(fin, linie)) {
			string curent, tip, model, culoare;
			int an, pret, crt = 0;
			std::stringstream linestream(linie);
			while (getline(linestream, curent, ',')) {
				if (crt == 0) tip = curent;
				if (crt == 1) model = curent;
				if (crt == 2) an = stoi(curent);
				if (crt == 3) culoare = curent;
				if (crt == 4) pret = stoi(curent);
				crt++;
			}
			Device dev{ tip, model, an, culoare, pret };
			devices.push_back(dev);
		}
		fin.close();
	}
	catch (RepoException& e) {
		std::cout << e.getError();
	}

}