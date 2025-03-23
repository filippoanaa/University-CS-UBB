#pragma once
#include<string>
using std::string;
class	Procesor
{
private:
	string numeProcesor, socluPr;
	int nrT = 0, pretProcesor = 0;
public:
	Procesor(string nume, string socluPr, int nrT, int pret) :numeProcesor{ nume }, socluPr{ socluPr }, nrT{ nrT }, pretProcesor{ pret } {};
	Procesor() = default;
	string getNumeProcesor()const;
	string getSocluProcesor()const;
	int getNrT()const;
	int getPretProceor()const;

};

class PlacaDeBaza {
	string numePlaca, socluPl;
	int pretPlaca = 0;
public:
	PlacaDeBaza(string nume, string soclu, int pret) :numePlaca{ nume }, socluPl{ soclu }, pretPlaca{ pret } {};
	PlacaDeBaza() = default;
	string getNumePlaca()const;
	string getSocluPlaca()const;
	int getPretPlaca()const;
};

