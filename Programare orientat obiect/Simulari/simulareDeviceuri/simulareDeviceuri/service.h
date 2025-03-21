#pragma once
#include<repo.h>
class Service
{
private:
	Repo& repo;

public:
	Service(Repo& repo) :repo{ repo } {};
	std::vector<Device>& getAllDevices() {
		return repo.getAll();
	}
	std::vector<Device> sorteazaModel();
	std::vector<Device> sorteazaAn();

};

