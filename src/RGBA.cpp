#include "RGBA.h"

RGBA::RGBA()
: r(0), g(0), b(0), a(0)
{}

RGBA::RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: r(r), g(g), b(b), a(a)
{}

RGBA::~RGBA() {}

void RGBA::debugPrint() {
	printf ("RGBA (%d,%d,%d,%d)\n",r,g,b,a);
}
