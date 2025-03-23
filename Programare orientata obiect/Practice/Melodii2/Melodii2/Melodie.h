#pragma once
#include<string>
using std::string;
class Melodie
{
private:
	int id;
	string titlu, artist, gen;
public:
	//constructor
	Melodie(int id, string titlu, string artist, string gen) :id{ id }, titlu{ titlu }, artist{ artist }, gen{ gen } {};
	/*
	* Getter pentru id
	* return type - int
	*/
	int getId() const;

	/*
	* Getter pentru titlu
	* return type - string
	*/
	string getTitlu() const;

	/*
	* Getter pentru artist
	* return type - string
	*/
	string getArtist() const;

	/*
	* Getter pentru gen
	* return type - string
	*/
	string getGen() const;

};

