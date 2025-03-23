#pragma once
#include<Domeniu.h>
#include<vector>
#include<exception>
using std::vector;
using std::exception;
class RepoException :public exception {
private:
	string error;
public:
	RepoException(string errorMsg) : error{ errorMsg } {};
	string getError() {
		return error;
	}
};

class Repo
{
private:
	vector<Procesor> procesoare;
	vector <PlacaDeBaza> placi;
	string filename;
	void loadFromFile();
public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
	Repo(Repo& ot) = delete;
	vector<Procesor>& getProcesoare();
	vector<PlacaDeBaza>& getPlaci();
	void store(PlacaDeBaza& pl);


};

