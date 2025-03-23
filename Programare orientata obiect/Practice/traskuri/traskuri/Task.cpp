#include "Task.h"

int Task::getId() const
{
	return id;
}

string Task::getDesc() const
{
	return descriere;
}

vector<string> Task::getProgramatori() const
{
	return listaProgramatori;
}

string Task::getStare() const
{
	return stare;
}

void Task::setStare(const string& stareNoua)
{
	stare = stareNoua;
}
