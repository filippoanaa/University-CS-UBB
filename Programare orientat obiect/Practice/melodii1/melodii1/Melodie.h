#pragma once
#include<string>
using std::string;
class Melodie
{
private:
	int id, rank;
	string titlu, artist;
public:
	//constructor
	Melodie(int id, string titlu, string artist, int rank) :id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {};

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
	 * Getter pentru rank
	 * return type - int
	 */
	int getRank() const;

	/*
	 * Setter pentru rank
	 * RankNou - int, noul rang al melodiei
	 */
	void setRank(int RankNou);

	/*
	 * Setter pentru titlu
	 * TiluNou - string, noul titlu al melodiei
	 */
	void setTitlu(string TiluNou);

};

