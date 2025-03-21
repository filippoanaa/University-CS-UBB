#pragma once
#include<string>
#include<vector>
#include<Task.h>
using std::vector;
using std::string;
class ValException {
private:
	vector<string> errors;
public:
	ValException(vector<string>errors) :errors{ errors } {};
	string getErrorMessage() const {
		string error;
		for (const auto& e : errors)
			error += e + "\n";
		return error;
	}

};

class Validator {
public:
	vector<string> errors;
	void valideaza(Task& t) {
		if (t.getId() < 0)
			errors.push_back("id-ul nu poate fi numar negativ");
		if (t.getDesc() == "")
			errors.push_back("Descrierea nu poate fi vida!");
		vector<string> stari = { "done","inprogress","closed" };
		if (t.getStare() != "done" && t.getStare() != "closed" && t.getStare() != "inprogress")
			errors.push_back("Stare invalida!");
		if (t.getProgramatori().size() < 1 && t.getProgramatori().size() > 4)
			errors.push_back("Numar invalid de programatori");
		if (errors.size() > 0)
			throw ValException(errors);

	}
};