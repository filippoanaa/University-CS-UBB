#include "Teste.h"
#include<assert.h>
void Teste::testDomeniu()
{
	Melodie m{ 1,"titlu","artist","pop" };
	assert(m.getId() == 1);
	assert(m.getTitlu() == "titlu");
	assert(m.getArtist() == "artist");
	assert(m.getGen() == "pop");
}

void Teste::testLoad()
{
	Repo repo{ "test.txt" };
	assert(repo.getAll().size() == 2);
	assert(repo.getAll()[0].getId()==3);
}

void Teste::testAddDelete()
{
	Repo repo{ "testAdd.txt" };
	Service srv{ repo };
	assert(repo.getAll().size() == 0);
	srv.storeMelodie("titlu1", "artist1", "rock");
	assert(repo.getAll().size() == 1);

	srv.removeMelodie(1, "titlu1", " artist1", "rock");
	assert(repo.getAll().size() == 0);
}


void Teste::testAddService()
{
	Repo repo{ "testAddS.txt" };
	Service srv{ repo };
	assert(srv.getAllMelodii().size() == 0);
	try {
		srv.storeMelodie("titlu", "artist", "vfgh");
		assert(false);
	}
	catch (std::exception) {
		assert(true);
	}
	assert(srv.getAllMelodii().size() == 0);

}

void Teste::testAll()
{
	testDomeniu();
	testLoad();
	testAddDelete();
	testAddService();
}
