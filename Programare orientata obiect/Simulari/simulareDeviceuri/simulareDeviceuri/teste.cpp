#include "teste.h"
#include<device.h>
#include<repo.h>
#include<service.h>
#include<cassert>
void testDomeniu() {
	Device dev{ "tip1","model1",2012,"rosu",500 };
	assert(dev.getTip() == "tip1");
	assert(dev.getCuloare() == "rosu");
	assert(dev.getAn() == 2012);
	assert(dev.getPret() == 500);
	Device dev2;
	assert(dev2.getAn() == 0);
	assert(dev2.getPret() == 0);
}

void testSorteazaModel() {
	Repo repo{ "test.txt" };
	Service srv{ repo };
	auto sortare = srv.sorteazaModel();
	assert(sortare[0].getModel() == "aa");
}
void testSorteazaAn() {
	Repo repo{ "test.txt" };
	Service srv{ repo };
	auto sortare = srv.sorteazaAn();
	assert(sortare[0].getAn() == 1999);
}

void testLoad() {
	Repo repo{ "test.txt" };
	assert(repo.getAll().size() == 3);
	assert(repo.getAll()[0].getTip() == "tip2");

}
void testAll()
{
	testDomeniu();
	testSorteazaModel();
	testSorteazaAn();
	testLoad();
}
