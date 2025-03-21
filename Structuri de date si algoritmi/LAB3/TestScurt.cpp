#include <assert.h>
#include<iostream>
#include "LO.h"
#include "Iterator.h"

#include <exception>

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

void testAll() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator itCauta = lo.cauta(1);
    assert(itCauta.valid());
    assert(itCauta.element() == 1);
    itCauta.urmator();
    assert(!itCauta.valid());
    itCauta.prim();
    assert(itCauta.valid());
    Iterator itPrim = lo.prim();
    assert(itPrim.valid());
    assert(itPrim.element() == 1);
    assert(lo.sterge(itCauta) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());
}

void testNou() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    lo.adauga(2);
    lo.adauga(3);
    lo.adauga(4);
    lo.adauga(5);
    lo.adauga(6);
    assert(lo.eliminaDinKinK(2) == 3);
    assert(lo.dim() == 3);
    Iterator itc = lo.cauta(2);
    assert(itc.valid());

    LO lo1 = LO(relatie1);
    assert(lo1.vida());
    assert(lo1.eliminaDinKinK(2) == 0);

}
