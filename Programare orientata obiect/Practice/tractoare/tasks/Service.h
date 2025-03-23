#pragma once
#include<Repo.h>
#include<Validator.h>
#include <set>
class Service
{
private:
	vector<Tractor> tractoare;
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};
	/*
	 * Returneaza toate tractoarele din repo.
	 * return type - vector<Tractor>&
	 */
	vector<Tractor>& getAllTractoare();

	/*
	 * Adauga un tractor nou.
	 * id - int, ID-ul tractorului.
	 * denumire - string, denumirea tractorului.
	 * tip - string, tipul tractorului.
	 * roti - int, numarul de roti al tractorului.
	 */
	void adaugaTractor(int id, string denumire, string tip, int roti);

	/*
	 * Returneaza o lista cu tipuri distincte de tractoare.
	 * return type - vector<string>
	 */
	vector<string> tipuriDistincte();

	/*
	 * Actualizeaza numarul de roti al unui tractor.
	 * id - int, ID-ul tractorului de actualizat.
	 */
	void updateNrRoti(int id);
};

