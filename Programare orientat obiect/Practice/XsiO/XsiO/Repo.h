#pragma once
#include<Domeniu.h>
#include<vector>
#include<exception>
using std::vector;
using std::exception;
class RepoException:public exception {
private:
	string error;
public:
	RepoException(string error) :error{ error } {};
	string getError() const {
		return error;
	}
};
class Repo
{
private:
	vector<Game> games;
	string filename;
	void loadFromFile();
	void saveToFile(vector<Game>& games);

public:
	//constructor
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	};

	/*
	* Functie care returneaza vectorul de jocuri
	* return type: vector<Game>& - referinta la vectorul de jocuri
	*/
	vector<Game>& getAll();

	/*
	* Verifica daca exista un joc cu ID-ul dat
	* id - int, ID-ul jocului verificat
	* return type: bool - true daca exista, false in caz contrar
	*/
	bool exist(int id);


	/*
	* Adauga un joc in vectorul de jocuri
	* Arunca RepoException daca exista deja un joc cu acelasi ID
	* g - Game&, referinta la jocul de adaugat
	*/
	void add(Game& g);

	/*
	* Gaseste un joc cu ID-ul specificat
	* id - int, ID-ul jocului de gasit
	* return type: Game& - referinta la jocul gasit
	* Arunca RepoException daca jocul nu este gasit
	*/
	Game& find(int id);

	/*
	* Modifica jocul identificat prin ID-ul dat
	* id - int, ID-ul jocului care se doreste a fi modificat
	* newDim - int, noua dimensiune a tablei de joc
	* newBoard - string, noua configuratie a tablei de joc
	* newGamer - char, noul jucator activ
	* newStatus - string, noul status al jocului
	*/
	void update(int id, int newDim, const string& newBoard, char newGamer, const string& newStatus);
};

