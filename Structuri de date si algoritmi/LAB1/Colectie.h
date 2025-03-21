#pragma once

#define NULL_TELEM (-1)
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	TElem* v;
	int nr_elem; //dimensiunea actuala
	int cp; //capacitatea
	int vmin;
	int vmax;
	int n; // nr de elemente
	void redim();
public:
	void debug() const;
	//constructorul implicit
	Colectie();
	// supraincarcam operatorul de indexare

	TElem& operator[](int index)
	{
		return v[index];
	}

	TElem operator[](int index) const
	{
		return v[index];
	}
	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

	int eliminaNAparitii(int n, TElem e);
};

