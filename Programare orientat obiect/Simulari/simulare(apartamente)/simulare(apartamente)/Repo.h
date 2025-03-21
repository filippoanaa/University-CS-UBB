#pragma once
#include<Apartament.h>
#include<vector>
#include<exception>
using std::exception;
using std::vector;

class RepoException :public exception {
private:
	string error;
public:
	RepoException(string error) :error{ error } {};
	string getError() {
		return error;
	}
};
class Repo
{
private:
	vector<Apartament> apartamente;
	string filename;
	void loadFromFile();
	void saveToFile(vector<Apartament>& apartamente);
public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
	vector<Apartament>& getAll();
	void remove(const string& strada, int supraf, int pret);



};

