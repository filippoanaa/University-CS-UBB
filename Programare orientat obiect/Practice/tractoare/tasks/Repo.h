#pragma once
#include<Tractor.h>
#include<exception>
#include<vector>
using std::exception;
using std::vector;
class RepoExceptions : public exception {
private:
	string error;
public:
	RepoExceptions(string error) :error{ error } {};
	string getError() const{
		return error;
	}
};
class Repo
{
private:
	vector<Tractor> tractoare;
	string filename;
	void loadFromFile();
	void saveToFile();
public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
    /*
     * Getter pentru lista de tractoare.
     * return type - vector<Tractor>&
     */
    vector<Tractor>& getTractoare();

    /*
     * Verifica daca un tractor exista in repo.
     * id - int, id-ul dupa care se cauta tractorul
     * return type - bool, true daca tractorul exista, false in caz contrar.
     */
    bool exista(int id);

    /*
     * Adauga un tractor in repo.
     * t - const Tractor&, tractorul de adaugat.
     * Arunca RepoExceptions daca tractorul exista deja.
     */
    void add(const Tractor& t);

    /*
     * Gaseste un tractor dupa ID.
     * id - int, ID-ul tractorului de gasit.
     * return type - Tractor&, referinta la tractorul gasit.
     * Arunca RepoExceptions daca tractorul nu este gasit.
     */
    Tractor& findTractor(int id);

    /*
     * Actualizeaza numarul de roti al unui tractor.
     * id - int, ID-ul tractorului de actualizat.
     * Arunca RepoExceptions daca tractorul nu este gasit.
     */
    void update(int id);

};

