#include "Service.h"
#include<exception>
vector<Melodie>& Service::getAllMelodii()
{
    return repo.getAll();
}

Melodie& Service::findMelodie(int id)
{

    for (int i = 0; i < getAllMelodii().size(); i++) {
        if (getAllMelodii()[i].getId() == id)
            return getAllMelodii()[i];
    }
}

void Service::updateMelodie(int id, string nouT, int nouR)
{
    Melodie& m = findMelodie(id);
    repo.update(m, nouT, nouR);
    
}

void Service::deleteMelodie(int id)
{
    Melodie& melodie = findMelodie(id);
    int fr = 0;
    for (auto m : getAllMelodii()) {
        if (m.getArtist() == melodie.getArtist())
            fr++;
    }
    if (fr > 1)
        repo.remove(id);
    else
        throw std::exception("Nu se poate sterge ultima melodie a artistului!");
}

vector<int> Service::frecventaRankuri()
{
    vector<int> ranks(11, 0);
    for (int i = 0; i < getAllMelodii().size(); i++) {
        int rank = getAllMelodii()[i].getRank();
        ranks[rank] += 1;
    }
    return ranks;
}
