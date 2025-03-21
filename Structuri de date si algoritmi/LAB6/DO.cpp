#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include<vector>
#include <exception>

const std::pair<int, int> NULL_TELEM(-1, -1);
using namespace std;

DO::DO(Relatie r) {
    rel = r;
    cap = MAX;
    primLiber = 0;
    size = 0;

    for (int i = 0; i < cap; i++) {
        urm[i] = -1;
        table[i] = NULL_TELEM;
    }
}

int DO::actPrimLiber() {
    primLiber++;
    while (primLiber < cap && table[primLiber].first != -1)
        primLiber++;
    return primLiber;
}
int DO::d(TCheie c) {
    int poz=abs(c%cap);
    return poz;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
    int i = d(c), j = -1;

    if(table[i].first==-1){
        table[i].first=c;
        table[i].second=v;
        size++;
        if(i==primLiber)
            actPrimLiber();
        return NULL_TVALOARE;
    }
    // Parcurgem lista de coliziuni pentru a gasi fie cheia existenta, fie locul unde să inseram noua pereche
    while (i != -1 && table[i].first != c && rel(table[i].first, c)) {
        j = i;
        i = urm[i];
    }

    if (i != -1 && table[i].first == c) { // cheie existenta
        TValoare old = table[i].second;
        table[i].second = v;
        return old;
    } else { // cheie noua, trebuie sa adaugam
        if (primLiber >= cap) {
            return NULL_TVALOARE;
        }

        // Inserez noua pereche la primLiber
        size++;
        table[primLiber].first = c;
        table[primLiber].second = v;

        if (j == -1) { // Lista de coliziuni este goala pentru această cheie
            urm[primLiber] = urm[d(c)]; //urm elem din lista de coliziuni devine urmatorul noului elem adaugat
            urm[d(c)] = primLiber;
        } else { // Inserez între j și i
            urm[primLiber] = urm[j];
            urm[j] = primLiber;
        }

        actPrimLiber();
        return NULL_TVALOARE;
    }
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) {
    int i = d(c);
    while (i != -1 && table[i].first != c) {
        i = urm[i];
    }
    if (i == -1)
        return NULL_TVALOARE;
    else
        return table[i].second;
}
//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
    int i = d(c);
    int j = -1;
    int k = 0;
    while (k < cap && j == -1) {
        if (urm[k] == i)
            j = k;
        else
            k++;
    }
    while (i != -1 && table[i].first != c) {
        j = i;
        i = urm[i];
    }
    if (i == -1) {
        return NULL_TVALOARE;
    } else {
        bool gata = false;

        do {
            int p = urm[i];
            int pp = i;
            while (p != -1 && d(table[p].first) != i) {
                pp = p;
                p = urm[p];
            }
            if (p == -1) {
                gata = true;
            } else {
                table[i] = table[p];
                j = pp;
                i = p;
            }
        } while (!gata);
        if (j != -1) {
            urm[j] = urm[i];
        }
        table[i].first = -1;
        urm[i] = -1;
        if (primLiber > i) {
            primLiber = i;
        }
        size--;
        return table[i].second;
    }

}
//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
    return size;
}
//verifica daca dictionarul e vid
bool DO::vid() const {
    return size == 0;
}
Iterator DO::iterator() const {
    return Iterator(*this);
}

TCheie DO::cheieMax() const {
    TCheie cheieMax=NULL_TCHEIE;
    if(size==0)
        return NULL_TCHEIE;
    for(int i=0;i<cap;i++){
        int curent=i;
        while(curent!=-1){
            if(table[curent].first>cheieMax)
                cheieMax=table[curent].first;
            else
                curent=urm[curent];
        }
    }
    return cheieMax;
}

DO::~DO() {
}