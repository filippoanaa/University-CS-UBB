#pragma once
#include<Repo.h>
#include<Validator.h>
#include<Observer.h>
class Service : public Observable
{
private:
	vector<Task> tasks;
	Validator& val;
	Repo& repo;
public:
	//constructor
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};

	/*
* Functie care returneaza lista de task-uri
* return type - vector<Task> - vectorul de task-uri
*/
	vector<Task>& getAllTasks();

	/*
	* Valideaza un task si il adauga in lista de task-uri
	* Arunca ValException daca datele nu sunt valide
	* id - int, id-ul task-ului
	* desc - string, descrierea task-ului
	* programatori - vector<string>, lista de programatori asociati cu task-ul
	* stare - string, starea task-ului
	*/
	void storeTask(int id, const string& desc, const vector<string>& programatori, const string& stare);

	/*
	* Gaseste task-urile unui programator
	* progr - string, numele programatorului a carui task-uri se cauta
	* return type - vector<Task> - lista de task-uri asociate cu programatorul
	*/
	vector<Task> findTasks(const string& progr);

	/*
	* Gaseste task-urile cu starea specificata
	* stare - string, starea dupa care se cauta
	* return type - vector<Task> - lista de task-uri cu starea respectiva
	*/
	vector<Task> findStare(const string& stare);

	/*
	* Modifica starea unui task identificat dupa id
	* id - int, id-ul task-ului care urmeaza sa fie modificat
	* stare - string, noua stare
	*/
	void updateStare(int id, const string& stare);

};

