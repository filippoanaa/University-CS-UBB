#include "Matrice.h"

#include <exception>

using namespace std;


Matrice::Matrice(int m, int n) {
    if (m < 0 || n < 0)
        return;
    cap = 1;
    linii = m;
    coloane = n;
    valori = 0;
    elem = new Triplet[cap];
    urm = new int[cap];
    for (int i = 0; i < cap - 1; i++)
        urm[i] = i + 1;
    urm[cap - 1] = -1;
    primLiber = 0;
    prim = -1;
    ultim = -1;


}

int Matrice::aloca() {
    int i = primLiber;
    primLiber = urm[primLiber];
    return i;
}

void Matrice::dealoca(int i) {
    urm[i] = primLiber;
    primLiber = i;
}

int Matrice::creeazaNod(Triplet e) {
    int i = aloca();
    if (i != -1) {
        elem[i] = e;
        urm[i] = -1;
    }
    return i;
}

void Matrice::redim() {
    primLiber = cap - 1;
    int newCap = cap * 2;
    PTriplet newElem = new Triplet[newCap];
    int *newUrm = new int[newCap];
    for (int i = 0; i < valori; i++) {
        newElem[i] = elem[i];
        newUrm[i] = urm[i];
    }
    for (int i = valori; i < newCap - 1; i++) {
        newUrm[i] = i + 1;
    }
    newUrm[newCap - 1] = -1;
    delete[]elem;
    delete[]urm;
    elem = newElem;
    urm = newUrm;
    cap = newCap;

}

int Matrice::nrLinii() const {
    return linii;
}

int Matrice::nrColoane() const {
    return coloane;
}

TElem Matrice::element(int i, int j) const {
    if (i < 0 || j < 0 || i > linii || j > coloane)
        return -1;
    int indiceCurent = prim;
    while (indiceCurent != -1) {
        if (elem[indiceCurent].linie == i && elem[indiceCurent].coloana == j)
            return elem[indiceCurent].val;
        indiceCurent = urm[indiceCurent];
    }
    return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i > linii || j > coloane)
        return -1;
    int indice = prim;
    int ant = -1;
    while (indice != -1 && (elem[indice].linie != i || (elem[indice].linie == i && elem[indice].coloana != j))) {
        ant = indice;
        indice = urm[indice];
    }
    if (indice != -1 && elem[indice].linie == i && elem[indice].coloana == j) {
        TElem vechi = elem[indice].val;
        if (e == NULL_TELEMENT) {
            //caz de stergere, se sterge primul element
            if (indice == prim) {
                prim = urm[prim];
            } else {
                //se parcurge pana la indice
                int q = urm[prim];
                while (urm[q] != indice) {
                    q = urm[q];
                }
                //q este nodul precedent a lui indice
                urm[q] = urm[indice];
            }
            dealoca(indice);
            valori--;
        } else {
            //caz de inlocuire
            elem[indice].val = e;
        }
        return vechi;
    }
    //caz de adaugare
    if (e != NULL_TELEMENT) {
        int nou = creeazaNod({i, j, e});
        ++valori;
        if (primLiber == -1) {
            //nu mai exista spatiu, suntem la sf listei
            redim();
            primLiber = valori;
        }
        if (prim == -1) {
            //lista e vida
            prim = nou;
            ultim = nou;
        } else {
            if (indice == prim) {
                //adauga inaintea primului
                urm[nou] = prim;
                prim = nou;
            } else if (indice == -1) {
                //adauga pe ultima pozitie
                urm[ultim] = nou;
                ultim = nou;
            } else {
                //adauga dupa
                urm[nou] = urm[ant];
                urm[ant] = nou;
            }

        }
    }
    return NULL_TELEMENT;

}

Matrice Matrice::transpusa() const {
    Matrice transpusa(coloane, linii);
    for (int i = 1; i <= linii; i++) {
        for (int j = 1; j <= coloane; j++) {
            TElem el = element(i, j);
            transpusa.modifica(j, i, el);
        }
    }
    return transpusa;
}


