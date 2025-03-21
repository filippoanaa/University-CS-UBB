#pragma once
#include<Task.h>
#include<exception>
using std::exception;
class RepoException : public exception {
private:
	string error;
public:
	RepoException(string error) :error{ error } {};
	string getError() const {
		return error;
	}

};
class Repo
{
private:
	vector<Task> tasks;
	string filename;
	void loadFromFile();
	void saveToFile();
public:
	//constructor 
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	};

	/*
	* Functie care returneaza vectorul de task-uri
	* return type: vector<Task> - vectorul de task-uri
	*/
	vector<Task>& getAll();

	/*
	* Verifica daca un task exista, dupa id-int
	* t - Task&, task-ul pentru care se verifica existenta
	* return type: bool - true daca task-ul exista, false in caz contrar
	*/
	bool exist(Task& t);

	/*
	* Adauga un Task in lista de task-uri, arunca RepoException daca exista deja
	* task cu acelasi id
	* t - Task&, task-ul care urmeaza sa fie adaugat
	*/
	void store(Task& t);

};

