#include "Domeniu.h"

int Game::getId() const
{
    return id;
}

int Game::getDim() const
{
    return dim;
}

string Game::getBoard() const
{
    return board;
}

char Game::getGamer() const
{
    return gamer;
}

string Game::getStatus() const
{
    return status;
}
