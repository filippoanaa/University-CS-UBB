#pragma once
#include<string>
using std::string;
class Stock
{
private:
	string id, nume;
	float pret;
	int mchange;

public:
	Stock(string id, string nume, float pret, int mchange) :id{ id }, nume{ nume }, pret{ pret }, mchange{ mchange } {};
	string getId() const;
	string getNume() const;
	float getPret() const;
	int getMChange() const;

};










