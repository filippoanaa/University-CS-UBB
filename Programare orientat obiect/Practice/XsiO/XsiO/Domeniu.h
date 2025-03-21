#pragma once
#include<string>
using std::string;
class Game
{
private:
	int id, dim;
	char gamer;
	string board, status;
public:
	//constructor
	Game(int id, int dim, string board, char gamer, string status) :id{ id }, dim{ dim }, board{ board }, gamer{ gamer }, status{ status } {};

    /*
* Getter pentru id
* return type: int - ID-ul jocului
*/
    int getId() const;

    /*
    * Getter pentru dimensiune
    * return type: int - dimensiunea tablei de joc
    */
    int getDim() const;

    /*
    * Getter pentru tabla de joc
    * return type: string - configuratia tablei de joc
    */
    string getBoard() const;

    /*
    * Getter pentru jucator
    * return type: char - jucatorul curent
    */
    char getGamer() const;

    /*
    * Getter pentru status
    * return type: string - statusul jocului
    */
    string getStatus() const;

    /*
    * Setter pentru dimensiune
    * newD - int, noua dimensiune a tablei de joc
    */
    void setDim(int newD) { dim = newD; }

    /*
    * Setter pentru tabla de joc
    * newB - string, noua configuratie a tablei de joc
    */
    void setBoard(string newB) { board = newB; }

    /*
    * Setter pentru jucator
    * newG - char, noul jucator curent
    */
    void setGamer(char newG) { gamer = newG; }

    /*
    * Setter pentru status
    * newS - string, noul status al jocului
    */
    void setStatus(string newS) { status = newS; }
};

