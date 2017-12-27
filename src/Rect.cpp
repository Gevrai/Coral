#include "Rect.h"

Rect::Rect()
	: x(0), y(0), w(0), h(0)
{}

Rect::Rect(int x, int y, int w, int h)
	: x(x)
	, y(y)
	, w(w)
	, h(h)
{}

Rect::Rect(const SDL_Rect &rect)
	: x(rect.x)
	, y(rect.y)
	, w(rect.w)
	, h(rect.h)
{}

SDL_Rect Rect::getSDL_Rect() {
	SDL_Rect sdlrect;
	sdlrect.x = x;
	sdlrect.y = y;
	sdlrect.w = w;
	sdlrect.h = h;
	return sdlrect;
}

// FIXME this will not work
bool Rect::Collide(const Rect &r)
{
	return false;
}
