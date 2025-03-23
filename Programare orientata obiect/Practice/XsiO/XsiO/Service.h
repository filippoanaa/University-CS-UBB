#pragma once
#include<Repo.h>
#include<Validator.h>

class Service
{
private:
	Repo& repo;
	Validator& val;

public:
	//constructor
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};

	/*
	* Returneaza toate jocurile din repository
	* return type: vector<Game>& - referinta la vectorul de jocuri
	*/
	vector<Game>& getAllGames();

	/*
	* Adauga un nou joc in repository
	* id - int, ID-ul jocului
	* dim - int, dimensiunea tablei de joc
	* board - const string&, tabla de joc initiala
	* gamer - char, jucatorul care incepe jocul
	* Arunca ValException daca jocul nu este valid
	* Arunca RepoException daca exista deja un joc cu acelasi ID
	*/
	void addGame(int id, int dim, const string& board, char gamer);

	/*
	* Actualizeaza un joc existent din repository
	* id - int, ID-ul jocului care trebuie actualizat
	* dim - int, noua dimensiune a tablei de joc
	* board - const string&, noua configuratie a tablei de joc
	* gamer - char, noul jucator activ
	* status - const string&, noul status al jocului
	* Arunca ValException daca jocul nu este valid
	* Arunca RepoException daca jocul nu este gasit in repository
	*/
	void update(int id, int dim, const string& board, char gamer, const string& status);
};
