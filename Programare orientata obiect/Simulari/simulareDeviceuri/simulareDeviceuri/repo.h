#pragma once
#include<string>
#include<device.h>
#include<exception>
#include<vector>
using std::exception;
using std::string;

class RepoException :public exception {
private:
	string error;
public:
	RepoException(string errorMsg) :error{ errorMsg } {};
	string getError() {
		return error;
	}
};
class Repo
{
private:
	std::vector<Device> devices;
	string filename;
	void loadFromFile();

public:
	Repo(string filename) :filename{ filename } {
		loadFromFile();
	}
	std::vector<Device>& getAll() {
		return devices;
	}



};

