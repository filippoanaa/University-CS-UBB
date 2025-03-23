#pragma once
#include <string>
using std::string;
class Tractor{
private:
	int id=0, nrRoti=0;
	string denumire, tip;
public:
	//constructor
	Tractor(int id, string denumire, string tip, int nrRoti) :id{ id }, denumire{ denumire }, tip{ tip }, nrRoti{ nrRoti } {};

	//constructor default
	Tractor() = default;
    /*
     * Returneaza ID-ul tractorului.
     * return type - int
     */
    int getId() const;

    /*
     * Returneaza denumirea tractorului.
     * return type - string
     */
    string getDenumire() const;

    /*
     * Returneaza tipul tractorului.
     * return type - string
     */
    string getTip() const;

    /*
     * Returneaza numarul de roti al tractorului.
     * return type - int
     */
    int getNrRoti() const;

    /*
     * Decrementeaza numarul de roti al tractorului cu 2.
     */
    void decrementNrRoti() { this->nrRoti -= 2; }

};

