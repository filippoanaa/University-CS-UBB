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
public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
    /*salveaza datele in fisier
    * melodii - vector<Melodie>&, vectorul de melodii salvat
     */
    void saveToFile(vector<Melodie>& melodii);
    /*
    * Getter pentru lista de melodii
    * return type - vector<Melodie>&
    */
    vector<Melodie>& getAll();

    /*
     * Actualizeaza o melodie
     * m - Melodie&, melodie de actualizat
     * titluNou - string, noul titlu
     * rankNou - int, noul rang
     */
    void update(Melodie& m, string titluNou, int rankNou);

    /*
     * Sterge o melodie dupa id
     * id - int, id-ul melodiei de sters
     */
    void remove(int id);

};

