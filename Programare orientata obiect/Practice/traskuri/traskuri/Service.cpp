#include "Service.h"
#include<algorithm>
#include <iterator>

vector<Task>& Service::getAllTasks()
{
	return repo.getAll();
}

void Service::storeTask(int id, const string& desc, const vector<string>& programatori, const string& stare)
{
	Task t{ id,desc,programatori,stare };
	val.valideaza(t);
	repo.store(t);
	notify();
}

vector<Task> Service::findTasks(const string& progr)
{
	vector<Task> tasks;
	vector<Task> allTasks = getAllTasks();
	std::copy_if(allTasks.begin(), allTasks.end(), back_inserter(tasks), [&](Task& t) {
		vector<string> programatori = t.getProgramatori();
		for (const auto& pr : programatori)
			if (pr == progr)
				return true;
		return false;
		});
	return tasks;
}

vector<Task> Service::findStare(const string& stare)
{
	vector<Task> tasks;
	vector<Task> allTasks = getAllTasks();
	std::copy_if(allTasks.begin(), allTasks.end(), back_inserter(tasks), [&](Task& t) {
		return t.getStare() == stare;
		});
	return tasks;
}

void Service::updateStare(int id, const string& stare)
{
	for (auto& t : getAllTasks()) {
		if (t.getId() == id)
			t.setStare(stare);
	}
	notify();
}
