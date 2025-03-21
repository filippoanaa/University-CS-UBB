#pragma once
#include<Stock.h>
#include<vector>
#include<exception>
using std::exception;
using std::vector;

class RepoException :public exception {
private:
	string error;
public:
	//constructor
	RepoException(string error) :error{ error } {};
	//gettrer al erorii
	string getError() const {
		return error;
	}
};
class Repo
{
private:
	vector<Stock> stocks;
	string filename;
	void loadFromFile();
	void saveToFile(vector<Stock>& stocks);
public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
	vector<Stock>& getAll();
	void remove(const string& id);

};

