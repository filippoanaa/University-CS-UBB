#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO &lo) : lo(lo) {

    curent = &lo.nodes[lo.first];
}

void Iterator::prim() {
    curent = &lo.nodes[lo.first];
}

void Iterator::urmator() {
    if (!valid())
        throw std::exception();
    curent = &lo.nodes[curent->next];
}

bool Iterator::valid() const {
    return curent != &lo.nodes[NULL_TELEMENT];
}

TElement Iterator::element() const {
    if (!valid())
        throw std::exception();
    return curent->elem;
}


