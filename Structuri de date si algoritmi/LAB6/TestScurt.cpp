#include <assert.h>

#include "DO.h"
#include "Iterator.h"

#include <exception>
using namespace std;
#include <iostream>

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	DO dictOrd = DO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    assert(dictOrd.dim() == 1);
    assert(!dictOrd.vid());
    assert(dictOrd.cauta(1)!=NULL_TVALOARE);
    TValoare v =dictOrd.adauga(1,3);
    assert(v == 2);
    assert(dictOrd.cauta(1) == 3);
    Iterator it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	assert(e.second != NULL_TVALOARE);
    	it.urmator();
    }
    assert(dictOrd.sterge(1) == 3);
    assert(dictOrd.vid());

}

void testNou(){
    DO dict=DO(relatie1);
    assert(dict.dim()==0);
    assert(dict.vid());
    assert(dict.cheieMax()==NULL_TCHEIE);
    dict.adauga(1,2);
    dict.adauga(3,3);
    dict.adauga(5,4);
    dict.adauga(100,5);
    assert(dict.cheieMax()==100);
}
