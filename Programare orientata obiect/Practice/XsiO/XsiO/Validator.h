#pragma once
#include<Domeniu.h>
#include<vector>
#include<string>
using std::vector;
using std::string;

class ValException {
private:
	vector<string> errors;
public:
	ValException(vector<string>errors) :errors{ errors } {};
	string getErro() const {
		string errorMsg;
		for (const auto& e : errors)
			errorMsg += e + "\n";
		return errorMsg;
	}
};

class Validator {
public:
	bool allowedCharacters(const std::string& word) {
		for (const char& c : word) {
			if (c != 'X' && c != 'O' && c != '-') {
				return false;
			}
		}
		return true;
	}
	void validate(Game& g) {
		vector<string> errors;
		if (g.getDim() != 3 && g.getDim() != 4 && g.getDim() != 5)
			errors.emplace_back("Inavlid size!");
		if (g.getBoard().size() != (g.getDim() * g.getDim()))
			errors.emplace_back("Invalid board! It must have size*size characters.");
		for (unsigned int i = 0; i < g.getBoard().size(); i++)
			if (g.getBoard()[i] != 'X' && g.getBoard()[i] != 'O' && g.getBoard()[i] != '-')
			errors.emplace_back("The board must contain only X,O,-!");
		if(g.getGamer()!= 'X' && g.getGamer()!= 'O'){
			errors.emplace_back("Players can only be X and O");
		}
		if (g.getStatus() != "unstarted" && g.getStatus() != "inprogress" && g.getStatus() != "finished")
			errors.emplace_back("Invalid status! available states: unstarted, inprogress, finished");
		if (!errors.empty())
			throw ValException(errors);
	}
};

