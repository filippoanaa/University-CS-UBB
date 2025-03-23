#include "Service.h"

vector<Game>& Service::getAllGames()
{
	return repo.getAll();
}

void Service::addGame(int id, int dim, const string& board, char gamer)
{
	Game g{ id,dim,board,gamer,"unstarted" };
	val.validate(g);
	repo.add(g);
}

void Service::update(int id, int dim, const string& board, char gamer, const string& status)
{
	Game g{ id,dim,board,gamer,status };
	val.validate(g);
	repo.update(id, dim, board, gamer, status);
	
}


