#pragma once

#include <climits>

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

typedef struct {
    TElement elem;
    int next;
} Nod;

typedef Nod *Pnod;

#define NULL_TELEMENT 0
#define FREE_TELEMENT INT_MIN

class LO {
private:
    friend class Iterator;

private:
    /* aici reprezentarea */
    Pnod nodes;
    int first;
    Relatie rel;
    int size, cap;

    void resize();

public:
    // constructor
    LO(Relatie r);

    // returnare dimensiune
    int dim() const;

    // verifica daca LO e vida
    bool vida() const;

    // prima pozitie din LO
    Iterator prim() const;

    // returnare element de pe pozitia curenta
    //arunca exceptie daca poz nu e valid
    TElement element(Iterator poz) const;

    // adaugare element in LO a.i. sa se pastreze ordinea intre elemente
    void adauga(TElement e);

    // sterge element de pe o pozitie poz si returneaza elementul sters
    //dupa stergere poz e pozitionat pe elementul de dupa cel sters
    //arunca exceptie daca poz nu e valid
    TElement sterge(Iterator &poz);

    // cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
    Iterator cauta(TElement e) const;

    //destructor
    ~LO();

    int eliminaDinKinK(int k);

};
