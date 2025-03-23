#pragma once
#include<vector>
using std::vector;
class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;
public:
	void notify() {
		for (auto& o : observers)
			o->update();
	}
	void addObserver(Observer* o) {
		observers.push_back(o);
	}

};