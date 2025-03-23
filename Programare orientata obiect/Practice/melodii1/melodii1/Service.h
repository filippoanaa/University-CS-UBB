#pragma once
#include<Repo.h>
class Service
{
private: 
	Repo& repo;
	vector<Melodie> melodii;
public:
	Service(Repo& repo) :repo{ repo } {};
    /*
     * Getter pentru lista de melodii
     * return type - vector<Melodie>&
     */
    vector<Melodie>& getAllMelodii();

    /*
     * Gaseste o melodie dupa id
     * id - int, id-ul melodiei cautate
     * return type - Melodie&
     */
    Melodie& findMelodie(int id);

    /*
     * Actualizeaza detaliile unei melodii
     * id - int, id-ul melodiei de actualizat
     * nouT - string, noul titlu
     * nouR - int, noul rang
     */
    void updateMelodie(int id, string nouT, int nouR);

    /*
     * Sterge o melodie dupa id
     * id - int, id-ul melodiei de sters
     * Arunca o exceptie daca este ultima melodie a artistului
     */
    void deleteMelodie(int id);

    vector<int> frecventaRankuri();
};

