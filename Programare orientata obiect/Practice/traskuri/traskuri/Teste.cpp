#include "Teste.h"
#include<Task.h>
#include<Repo.h>
#include<Service.h>
#include<GUI.h>
#include<Validator.h>
#include <cassert>
#include <fstream>
#include <iostream>
//domeniu
void Tests::testDoemniu() {
	Task t{ 5,"app",{ "oana", "robert" } ,"done" };
	assert(t.getDesc() == "app");
	assert(t.getId() == 5);
	assert(t.getProgramatori().size() == 2);
	assert(t.getStare() == "done");
	t.setStare("closed");
	assert(t.getStare() == "closed");
}
//repo
void Tests::testLoad() {
	Repo repo{ "tasks_test.txt" };
	std::cout << repo.getAll().size();
}

void Tests::testAddSave() {
	std::ofstream fout("tasks_test.txt");
	fout.close();  // Fisierul este acum gol

	Repo repo{ "tasks_test.txt" };
	Task t{ 5,"app",{ "oana", "robert" } ,"done" };
	repo.store(t);
	assert(repo.getAll().size() == 1);
	try {
		repo.store(t);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	assert(repo.getAll().size() == 1);
}

//service
void Tests::testAddSrv() {
	Repo repo{ "tasks_test.txt" };
	Validator val;
	Service srv(repo, val);
	try {
		srv.storeTask(100, "", { "a","b","c","d","e" }, "ceva");
		assert(false);
	}
	catch (ValException&) {
		assert(true);
	}

}

void Tests::testFindProg() {
	Repo repo{ "tasks_test.txt" };
	Validator val;
	Service srv(repo, val);
	auto tasks1 = srv.findTasks("anca");
	assert(tasks1.size() == 0);
	auto tasks2 = srv.findTasks("robert");
	assert(tasks2.size() == 1);
}

void Tests::testFindStare() {
	Repo repo{ "tasks_test.txt" };
	Validator val;
	Service srv(repo, val);
	auto tasks = srv.findStare("done");
	assert(tasks.size() == 1);
}

void Tests::testUpdateStare() {
	Repo repo{ "tasks_test.txt" };
	Validator val;
	Service srv(repo, val);
	assert(srv.findStare("inprogress").size() == 0);
	srv.updateStare(5, "inprogress");
	assert(srv.findStare("inprogress").size() == 1);
}


void Tests::testAll()
{
	testDoemniu();
	testLoad();
	testAddSave();
	testAddSrv();
	testFindProg();
	testFindStare();
	testUpdateStare();
}
