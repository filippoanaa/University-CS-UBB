#pragma once
#include <string>
using std::string;
class Device
{
private:
	string tip, model, culoare;
	int pret = 0, an = 0;
public:
	Device() = default;
	Device(string tip, string model, int an, string culoare, int pret) :tip{ tip }, model{ model }, an{ an }, culoare{ culoare }, pret{ pret } {};
	string getTip() const;
	string getModel() const;
	string getCuloare() const;
	int getPret() const;
	int getAn() const;

};

