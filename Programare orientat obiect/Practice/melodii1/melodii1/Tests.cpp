#include "Tests.h"
#include<Melodie.h>
#include<Repo.h>
#include<Service.h>
#include <cassert>
#include<fstream>
#include<qdebug.h>
void Tests::testDomeniu()
{
	Melodie mel{ 1,"titlu1","artist1",8 };
	assert(mel.getId() == 1);
	assert(mel.getTitlu() == "titlu1");
	assert(mel.getArtist() == "artist1");
	assert(mel.getRank() == 8);

	mel.setRank(9);
	mel.setTitlu("alt titlu");
	assert(mel.getRank() == 9);
	assert(mel.getTitlu() == "alt titlu");
}

void Tests::testUpdate()
{
	Repo repo{ "test.txt" };
	assert(repo.getAll().size() == 3);
	repo.update(repo.getAll()[1], "titluNou", 7);
	auto melActualizata = repo.getAll()[1];
	assert(melActualizata.getTitlu() == "titluNou");
	assert(melActualizata.getRank() == 7);

}

void Tests::testAll()
{
	testDomeniu();
	testUpdate();
}

