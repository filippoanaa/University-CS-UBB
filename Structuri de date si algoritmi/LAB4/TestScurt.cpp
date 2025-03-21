#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
    Matrice m(4, 4);
    assert(m.nrLinii() == 4);
    assert(m.nrColoane() == 4);
    //adaug niste elemente
    m.modifica(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modifica(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEMENT);
}

    void testNou() {
        Matrice m(4, 4);
        assert(m.nrLinii() == 4);
        assert(m.nrColoane() == 4);
        m.modifica(1, 3, 1);
        m.modifica(2, 3, 5);
        m.modifica(4, 1, 3);
        m.modifica(4, 3, 8);

        assert(m.element(1,3)==1);
        assert(m.element(2, 3) == 5);

        Matrice transpusa = m.transpusa();
        assert(m.nrColoane() == 4);
        assert(m.nrLinii() == 4);
        assert(transpusa.element(3,2)==5);
        assert(transpusa.element(3,1)==1);
    }
