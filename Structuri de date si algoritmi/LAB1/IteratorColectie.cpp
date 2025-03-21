#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>
#include <iostream>
using namespace std;


IteratorColectie::IteratorColectie(const Colectie& c)
	: col(c)
{
	if (col.dim() == 0)
	{
		numar = -1;
		index = -1;
		elem = 0;
		return;
	}

	for (int i = 0; i <= col.nr_elem; ++i)
	{
		if (col.v[i] > 0)
		{
			numar = col.v[i] - 1;
			index = i;
			elem = col.vmin + i;
			break;
		}
	}
}


void IteratorColectie::prim() {
	if (col.dim() == 0)
	{
		numar = -1;
		index = -1;
		elem = 0;
		return;
	}


	for (int i = 0; i <= col.nr_elem; ++i)
	{
		if (col.v[i] > 0)
		{
			numar = col.v[i] - 1;
			index = i;
			elem = col.vmin + i;
			break;
		}
	}
}

void IteratorColectie::urmator()
{
	if (numar > 0)
	{
		numar--;
	}
	else
	{
		bool found = false;
		for (int i = index + 1; i <= col.nr_elem; ++i)
		{
			if (col.v[i] > 0)
			{
				numar = col.v[i] - 1;
				index = i;
				elem = col.vmin + i;
				found = true;
				break;
			}
		}

		if (!found)
		{
			numar = -1;
			index = -1;
			elem = 0;
		}
	}
}

bool IteratorColectie::valid() const {
	return numar >= 0;
}

TElem IteratorColectie::element() const {
	if (valid())
	{
		return elem;
	}
	else
	{
		return -1;
	}
}
