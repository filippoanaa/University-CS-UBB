#include "Teste.h"
#include<assert.h>
#include<fstream>
void Teste::testDomeniu()
{
	Game g{ 1,3,"OOOOOOOOO",'X',"terminat" };
	assert(g.getId() == 1);
	assert(g.getDim() == 3);
	assert(g.getBoard() == "OOOOOOOOO");
	assert(g.getGamer() == 'X');
	assert(g.getStatus() == "terminat");
	g.setDim(4);
	g.setBoard("OOOOOOOOOXXXXXXX");
	g.setGamer('O');
	assert(g.getDim() == 4);
	assert(g.getBoard() == "OOOOOOOOOXXXXXXX");
	assert(g.getGamer() == 'O');
}

void Teste::testExistAdd()
{
	std::ofstream fout("gamesTest.txt");
	fout.close();
	Repo repo{ "gamesTest.txt" };
	Validator val;
	Service srv{ repo,val };
	assert(repo.getAll().size() == 0);
	Game g(1, 3, "XXXOOOXXX", 'X', "inprogress");
	repo.add(g);
	assert(repo.getAll().size() == 1);
	assert(repo.exist(1) == true);
	assert(repo.exist(10) == false);
	try {
		repo.add(g);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		srv.addGame(2, 100, "hgfrde", 'c');
		assert(false);
	}
	catch (ValException&) {
		assert(true);
	}
}

void Teste::testFind()
{
	std::ofstream fout("gamesTest.txt");
	fout.close();
	Repo repo{ "gamesTest.txt" };
	Game g(1, 3, "XXXOOOXXX", 'X', "inprogress");
	repo.add(g);
	Game game = repo.find(1);
	assert(game.getDim() == 3);
	assert(game.getGamer() == 'X');
}

void Teste::testUpdate()
{
	std::ofstream fout("gamesTest.txt");
	fout.close();
	Repo repo{ "gamesTest.txt" };
	Validator val;
	Service srv{ repo, val };
	srv.addGame(1, 3, "XXXOOOXXX", 'X');
	srv.update(1,3, "XXXOOOXXX", 'O', "finished");
	Game g = repo.find(1);
	assert(g.getGamer() == 'O');
	assert(g.getStatus() == "finished");
	try {
		srv.update(10, 10, "vfdsd", 's', "fgfds");
		assert(false);
	}
	catch (ValException&) {
		assert(true);
	}
}

void Teste::testAll()
{
	testDomeniu();
	testExistAdd();
	testFind();
	testUpdate();
}
