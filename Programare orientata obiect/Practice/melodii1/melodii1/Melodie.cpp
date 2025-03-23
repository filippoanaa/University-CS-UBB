#include "Melodie.h"

int Melodie::getId() const
{
    return id;
}

string Melodie::getTitlu() const
{
    return titlu;
}

string Melodie::getArtist() const
{
    return artist;
}

int Melodie::getRank() const
{
    return rank;
}

void Melodie::setRank(int rankNou)
{
    rank = rankNou;
}

void Melodie::setTitlu(string titluNou)
{
    titlu = titluNou;
}
