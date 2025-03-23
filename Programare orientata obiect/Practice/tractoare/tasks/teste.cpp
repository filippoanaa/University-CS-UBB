#include "teste.h"
#include<Tractor.h>
#include<Repo.h>
#include<Validator.h>
#include<Service.h>
#include <cassert>
#include<fstream>
void Teste::testDoemniu()
{
	Tractor tr{ 1,"tr","tip",4 };
	assert(tr.getId() == 1);
	assert(tr.getDenumire() == "tr");
	assert(tr.getTip() == "tip");
	assert(tr.getNrRoti() == 4);
	tr.decrementNrRoti();
	assert(tr.getNrRoti() == 2);
}

void Teste::testRepo()
{
	std::ofstream fout("test.txt");
	fout.close();
	Repo repo{ "test.txt" };
	//add/save
	assert(repo.getTractoare().size() == 0);
	Tractor t1{ 1,"tr1","tip1",4 };
	repo.add(t1);
	assert(repo.getTractoare().size() == 1);
	try {
		repo.add(t1);
		assert(false);
	}
	catch (RepoExceptions& ) {
		assert(true);
	}
	//load
	assert(repo.getTractoare()[0].getId() == 1);
	assert(repo.getTractoare()[0].getDenumire() == "tr1");
	assert(repo.getTractoare()[0].getTip() == "tip1");
	assert(repo.getTractoare()[0].getNrRoti() == 4);


	//exista
	assert(repo.exista(1) == true);
	assert(repo.exista(1234) == false);

	//find
	auto tr = repo.findTractor(1);
	assert(tr.getDenumire() == "tr1");
	assert(tr.getNrRoti() == 4);
	try {
		repo.findTractor(100);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}
	
	//update
	int nrRotiInitial = t1.getNrRoti();
	repo.update(1);
	auto trActualizat = repo.findTractor(1);
	assert(trActualizat.getNrRoti() == nrRotiInitial - 2);

}

void Teste::testService()
{
	std::ofstream fout("test.txt");
	fout.close();
	Repo repo{ "test.txt" };
	Validator val;
	Service srv{ repo, val };
	//adauga
	assert(srv.getAllTractoare().size() == 0);
	srv.adaugaTractor(1, "tr1", "tip1", 4);
	srv.adaugaTractor(2, "tr2", "tip2", 6);
	srv.adaugaTractor(3, "tr3", "tip3", 8);
	assert(srv.getAllTractoare().size() == 3);
	try {
		srv.adaugaTractor(4, "", "", 3);
		assert(false);
	}
	catch (ValException&) {
		assert(true);
	}
	assert(srv.getAllTractoare().size() == 3);

	//tipuri distincte
	auto tipuriDistincte = srv.tipuriDistincte();
	assert(tipuriDistincte.size() == 3);
	assert(tipuriDistincte[0] == "tip1");

	//update
	assert(srv.getAllTractoare()[0].getNrRoti() == 4);
	srv.updateNrRoti(1);
	assert(srv.getAllTractoare()[0].getNrRoti() == 2);
}

void Teste::testAll() {
	testDoemniu();
	testRepo();
	testService();
}