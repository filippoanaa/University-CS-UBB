#include <algorithm>
#include "Iterator.h"
#include "DO.h"

using namespace std;
const std::pair<int, int> NULL_TELEM(-1, -1);

bool Iterator::sortare(TElem a, TElem b) {
    return dict.rel(a.first, b.first);
}
Iterator::Iterator(const DO &d) : dict(d) {
    for (int i = 0; i < dict.cap; i++) {
        if (dict.table[i].second != NULL_TVALOARE) {
            v.push_back(dict.table[i]);
        }
    }
    sort(v.begin(), v.end(), [this](const TElem &a, TElem &b) {
        return sortare(a, b);
    });
    prim();
}
void Iterator::prim() {
    poz = 0;
}

void Iterator::urmator() {
    poz++;
}

bool Iterator::valid() const {
    return poz < v.size();
}

TElem Iterator::element() const {
    return v[poz];
}





