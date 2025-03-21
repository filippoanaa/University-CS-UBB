#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>
#include <cmath>
using namespace std;


Colectie::Colectie()
{
	cp = 4;                             // setam capacitatea
	v = new TElem[cp];                  // alocam spatiu de memorie pt vector
	memset(v, 0, cp * sizeof(TElem));   // setam memoria la 0
	nr_elem = 0;                        // dimensiune
	n = 0;                              // numarul total de elemente din colectie
	vmin = 0;                           //valoarea minima din vector
	vmax = 0;                           //valoarea maxima din vector
}


void Colectie::redim()
{

	TElem* vNou = new TElem[cp * 2];
	memset(vNou, 0, cp * 2 * sizeof(TElem));

	for (int i = 0; i <= nr_elem; ++i)
		vNou[i] = v[i];
	delete[] v;
	v = vNou;
	cp *= 2;
}

void Colectie::adauga(TElem elem) {
	n++;

	if (elem >= vmax)
	{
		// Elementul este mai mare decat vmax si pozitiv mereu
		// nu se translateaza sirul
		while (abs(vmin) + abs(elem) >= cp)
			redim();

		vmax = elem;
		v[abs(vmin) + elem]++;
		nr_elem = abs(vmin) + elem;
	}
	else
	{
		if (elem < vmin)
		{
			// Elementul este negativ si mai mic decat vmin
			int transl = vmin - elem; // toate elementee se translateaza spre dreapta cu transl

			// Redimensionam in caz ca e nevoie
			while (vmax + abs(vmin) + transl >= cp)
				redim();

			// Translatam
			for (int i = vmax + abs(vmin); i >= 0; --i)
				v[i + transl] = v[i];
			for (int i = 0; i < transl; ++i)
				v[i] = 0;

			v[0]++;  // aici adaugam minimul (elem)
			vmin = elem;
			nr_elem += transl;
		}
		else // daca elem este intre vmin si vmax - nu se translateaza sirul
		{
			if (elem >= 0)
			{
				v[abs(vmin) + elem]++;
			}
			else
			{
				v[elem - vmin]++;
			}
		}
	}
}

bool Colectie::sterge(TElem elem) {
	// Elementul e in afara minimului si maximului sigur nu il avem
	if (elem < vmin || elem > vmax)
		return false;

	if (elem >= 0)
	{
		// Elementul este pozitiv
		if (v[abs(vmin) + elem] > 0)
		{
			// Elementul exista
			v[abs(vmin) + elem]--;
			n--;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (v[elem - vmin] > 0)
		{
			v[elem - vmin]--;
			n--;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Colectie::cauta(TElem elem) const {
	if (elem < vmin || elem > vmax)
	{
		return false;
	}

	if (elem >= 0)
	{
		return v[abs(vmin) + elem] > 0;
	}
	else
	{
		return v[elem - vmin] > 0;
	}
}


int Colectie::nrAparitii(TElem elem) const {
	if (elem < vmin || elem > vmax)
	{
		//cout << "0 aparitii" << endl;
		return 0;
	}

	if (elem >= 0)
	{

		return v[abs(vmin) + elem];
	}
	else
	{

		return v[elem - vmin];
	}
}
int Colectie::dim() const {
	return n;
}

bool Colectie::vida() const {
	return nr_elem == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

Colectie::~Colectie() {
	delete[] v;
}


int Colectie::eliminaNAparitii(int n, TElem elem)
{
	int eliminari = 0;
	while (cauta(elem) && eliminari < n)
	{
		sterge(elem);
		eliminari++;
	}
	return eliminari;
}

