#pragma once
#include<string>
using std::string;
class Apartament
{
private:
	string strada;
	int suprafata = 0, pret = 0;
public:
	Apartament() = default;
	Apartament(string strada, int suprafata, int pret) :strada{ strada }, suprafata{ suprafata }, pret{ pret } {};
	string getStrada() const;
	int getSuprafata()const;
	int getPret()const;

};

