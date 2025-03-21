#include "Service.h"
#include <exception>

vector<Melodie>& Service::getAllMelodii()
{
    return repo.getAll();
}

void Service::storeMelodie(const string& titlu, const string& artist, const string& gen)
{
    if (gen != "pop" && gen != "rock" && gen != "folk" && gen != "disco")
        throw std::exception("Gen invalid!");
    Melodie m{ (int)repo.getAll().size() + 1 ,titlu,artist,gen};
    repo.store(m);
}

void Service::removeMelodie(int id, const string& titlu, const string& artist, const string& gen)
{
    Melodie m{ id,titlu,artist,gen };
    repo.remove(m);
}
