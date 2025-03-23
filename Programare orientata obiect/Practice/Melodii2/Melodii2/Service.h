#pragma once
#include<Repo.h>
#include<Validator.h>
class Service
{
private:
	Repo& repo;
	vector<Melodie> melodii;
public:
	Service(Repo& repo) :repo{ repo } {};
	/*
	* Getter pentru vectorul de melodii
	 * return type - vector<Melodie>&
	*/
	vector<Melodie>& getAllMelodii();

	/*
	 * Adauga o melodie in vectorul de melodii
	 * titlu - string, titlul melodiei
	 * artist - string, artistul melodiei
	 * gen - string, genul melodiei (pop, rock, folk, disco)
	 * Arunca: exception daca genul nu este unul dintre valorile acceptate (pop, rock, folk, disco)
	 */
	void storeMelodie(const string& titlu, const string& artist, const string& gen);

	/*
	 * Sterge o melodie din vectorul de melodii
	 * id - int, id-ul melodiei
	 * titlu - string, titlul melodiei
	 * artist - string, artistul melodiei
	 * gen - string, genul melodiei
	 * return type - void
	 */
	void removeMelodie(int id, const string& titlu, const string& artist, const string& gen);
};

