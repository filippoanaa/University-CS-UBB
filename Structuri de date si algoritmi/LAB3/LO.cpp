#include "Iterator.h"
#include "LO.h"


#include <iostream>
#include <climits>

using namespace std;

#include <exception>

LO::LO(Relatie r) {

    rel = r;
    size = 1;
    cap = 2;
    first = 0;
    nodes = new Nod[cap];
}


int LO::dim() const {
    return size - 1;
}

bool LO::vida() const {
    return size - 1 == 0;
}

Iterator LO::prim() const {
    Iterator it = Iterator(*this);
    it.prim();
    return it;
}

TElement LO::element(Iterator poz) const {
    if (!poz.valid())
        throw std::exception();
    return poz.element();
}

TElement LO::sterge(Iterator &poz) {
    if (!poz.valid())
        throw std::exception();
    TElement e = poz.element();
    poz.urmator();
    size--;

    if (e == nodes[first].elem) {
        nodes[first].elem = FREE_TELEMENT;
        first = nodes[first].next;
        return e;
    }

    int curr = first, prev;
    while (nodes[curr].elem != e) {
        prev = curr;
        curr = nodes[curr].next;
    }
    nodes[prev].next = nodes[curr].next;
    nodes[curr].elem = FREE_TELEMENT;
    return e;

}


Iterator LO::cauta(TElement e) const {

    Iterator it = Iterator(*this);
    it.prim();
    while (it.valid() && it.element() != e)
        it.urmator();
    return it;
}

void LO::adauga(TElement e) {


    if (first == 0) {
        first = 1;
        nodes[size++] = Nod{e, NULL_TELEMENT};
        return;
    }

    if (size == cap)
        resize();

    int freePos = -1;
    for (int i = 1; i < cap; i++) {
        if (nodes[i].elem == FREE_TELEMENT) {
            freePos = i;
            break;
        }
    }

    // adauga elem la inceputul listei
    if (rel(e, nodes[first].elem)) {
        nodes[freePos] = Nod{e, first};
        first = freePos;
        size++;
        return;
    }

    //adauga elem intre 2 noduri
    int curr = first, prev;
    while (rel(nodes[curr].elem, e) && curr != NULL_TELEMENT) {
        prev = curr;
        curr = nodes[curr].next;
    }
    nodes[prev].next = freePos;
    nodes[freePos] = Nod{e, curr};
    size++;

}

void LO::resize() {
    cap *= 2;
    Pnod newN = new Nod[cap];

    for (int i = 0; i < size; i++)
        newN[i] = nodes[i];
    for (int i = size; i < cap; i++)
        newN[i].elem = FREE_TELEMENT;

    delete[] nodes;
    nodes = newN;
}


LO::~LO() {
    delete nodes;
}


int LO::eliminaDinKinK(int k) {
    int sterse = 0;
    Iterator it = Iterator(*this);
    it.prim();
    while (it.valid()) {
        for (int i = 0; i < k && it.valid(); i++) {
            sterge(it);
            sterse++;
            it.urmator();
        }
    }
    return sterse;
}
