#include "Teste.h"
#include<Repo.h>
#include<Service.h>
#include <cassert>
void testRepo() {
	Repo repo1{ "test.txt" };
	assert(repo1.getAll().size() == 2);
	assert(repo1.getAll()[0].getPret() == 1000);
	assert(repo1.getAll()[0].getSuprafata() == 10);
	assert(repo1.getAll()[0].getStrada() == "strada1");
	try {
		Repo repo2{ "fdsxc.txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testService() {
	Repo repo1{ "test.txt" };
	Service srv1{ repo1 };
	assert(srv1.getAllAp().size() == 2);
	auto filtrare1 = srv1.filtrare(15, 70);
	assert(filtrare1.size() == 1);
	assert(filtrare1[0].getStrada() == "strada2");
	assert(srv1.filtrarePret(50, 1010).size() == 1);
	assert(srv1.filtrarePret(10000, 1000000).size() == 0);
}

void testDomeniu() {
	Apartament ap{ "strada",50,1200 };
	assert(ap.getStrada() == "strada");
	assert(ap.getSuprafata() == 50);
	assert(ap.getPret() == 1200);
	Apartament ap2;
	assert(ap2.getPret() == 0);
}
void TestAll() {
	testRepo();
	testService();
	testDomeniu();
}