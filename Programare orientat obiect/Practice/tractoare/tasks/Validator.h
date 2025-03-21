#pragma once
#include<vector>
#include<Tractor.h>
#include<string>
using std::vector;
using std::string;
class ValException {
private:
	vector<string> errorMessages;
public:
	ValException(vector<string> err) :errorMessages{ err } {};
	string getErrors() {
		string errors;
		for (const auto& e : errorMessages) {
			errors += e + "\n";
		}
		return errors;
	}
};
class Validator {
public:
	void valideaza(Tractor& tr) {
		vector<string> errors;
		if (tr.getDenumire().empty())
			errors.push_back("Denumirea nu poate fi vida!");
		if (tr.getTip().empty())
			errors.push_back("Tipul nu poate fi vid!");
		if (tr.getNrRoti() % 2 != 0 || (tr.getNrRoti() < 2 && tr.getNrRoti() > 16))
			errors.push_back("Numar invalid de roti!");

		if (!errors.empty())
			throw ValException(errors);
	}
};