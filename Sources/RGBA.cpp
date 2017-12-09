#include "RGBA.h"

RGBA::RGBA()
{
}

RGBA::RGBA(Uint8 nr, Uint8 ng, Uint8 nb, Uint8 na)
{
	r = nr;
	g = ng;
	b = nb;
	a = na;
}

RGBA::~RGBA()
{
}

RGBA::operator Uint32()
{
	// #TODO
	return NULL;
}
