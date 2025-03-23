#include "Repo.h"
#include<fstream>
#include<sstream>
#include <iostream>
#include<qdebug.h>
using std::ifstream;
using std::ofstream;
void Repo::loadFromFile()
{
	try {
        ifstream fin(this->filename);
        if (!fin.is_open()) {
            throw RepoException("Cannot read from file " + filename);
        }
        string line;
        while (getline(fin, line)) {
            if (!line.empty()) {
                int id = 0, dim = 0;
                string board, status;
                char gamer;
                std::stringstream linestream(line); 
                string currentItem;
                int itemNumber = 0;
                while (getline(linestream, currentItem, ' ')) {
                    if (itemNumber == 0) id = stoi(currentItem);
                    if (itemNumber == 1) dim = stoi(currentItem);
                    if (itemNumber == 2) board = currentItem;
                    if (itemNumber == 3) gamer = currentItem[0];
                    if (itemNumber == 4) status = currentItem;
                    itemNumber++;
                }
                Game g{ id,dim,board,gamer,status };
                games.push_back(g);
            }
        }
        fin.close();
		
	}
	catch (RepoException& e) {
		qDebug()<<e.getError();
	}

}

void Repo::saveToFile(vector<Game>& games)
{
    ofstream fout(filename);
    for (auto& g : games) {
        fout << g.getId() << " " << g.getDim() << " " << g.getBoard() << " " << g.getGamer() << " " << g.getStatus() << "\n";
    }
    fout.close();

}

vector<Game>& Repo::getAll()
{
	return games;
}

bool Repo::exist(int id)
{
    for (auto& g : getAll()) {
        if (g.getId() == id)
            return true;
    }
    return false;
}

void Repo::add(Game& g)
{
    if (exist(g.getId())) {
        throw RepoException("A game with this id already exists!");
    }
    games.push_back(g);
    saveToFile(games);
}

Game& Repo::find(int id)
{
    for (auto& g : games) {
        if (g.getId() == id)
            return g;
    }
    throw RepoException("No game found with this id!");
}

void Repo::update(int id, int newDim, const string& newBoard, char newGamer, const string& newStatus)
{
    Game& g= find(id);
    g.setDim(newDim);
    g.setBoard(newBoard);
    g.setGamer(newGamer);
    g.setStatus(newStatus);
    saveToFile(games); 
}
