#pragma once
#include<Melodie.h>
#include<vector>
using std::vector;
class Repo
{
private:
	vector<Melodie> melodii;
	string filename;

	void loadFromFile();
	void saveToFile(vector<Melodie>& melodii);

public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
	/*
	* Getter pentru vectorul de melodii
	* return type - vector<Melodie>&
	*/
	vector<Melodie>& getAll();

	/*
	 * Adauga o melodie in vectorul de melodii
	 * m - Melodie, melodie de adaugat
	 */
	void store(const Melodie& m);

	/*
	 * Sterge o melodie din vectorul de melodii
	 * m - Melodie, melodie de sters
	 * Arunca: std::exception daca melodie cu id-ul specificat nu exista in vector
	 */
	void remove(const Melodie& m);

};

