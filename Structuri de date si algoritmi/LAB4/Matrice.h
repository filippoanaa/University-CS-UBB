#pragma once

typedef int TElem;


#define NULL_TELEMENT 0

struct Triplet {
    int linie, coloana;
    TElem val;
};
typedef Triplet *PTriplet;

class Matrice {

private:
    int cap;
    int linii, coloane, valori;
    //vectorul static de elemente de tip Triplet
    PTriplet elem;
    //vectorul static pt legaturi, fiecare elem din matrice este asociat cu
    //un indice in vectorul elem, iar fiecare elem din vectorul urm indica indexul urmatorului
    //elem din lista
    int *urm;
    //referinta catre primul/ultimul elem al listie
    int prim, ultim;
    //referinta catre primul elem liber al listie
    int primLiber;

    //se returneaza pozitia spatiului liber in lista
    int aloca();

    //dealoca spatiul de la indicele i
    void dealoca(int i);

    int creeazaNod(Triplet e);

    void redim();


public:

    //constructor
    //se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
    Matrice(int nrLinii, int nrColoane);


    //destructor
    ~Matrice() {};

    //returnare element de pe o linie si o coloana
    //se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
    //indicii se considera incepand de la 0
    TElem element(int i, int j) const;


    // returnare numar linii
    int nrLinii() const;

    // returnare numar coloane
    int nrColoane() const;


    // modificare element de pe o linie si o coloana si returnarea vechii valori
    // se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    TElem modifica(int i, int j, TElem);
    Matrice transpusa() const;
};







