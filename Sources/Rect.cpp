#include "Rect.h"

Rect::Rect()
{
}

Rect::Rect(int nx, int ny, int nw, int nh)
{
	x = nx;
	y = ny;
	w = nw;
	h = nh;
}

Rect::Rect(SDL_Rect* rect)
{
	x = rect->x;
	y = rect->y;
	w = rect->w;
	h = rect->h;
}

Rect::Rect(Point* top, Point* bottom)
{
	x = top->x;
	y = top->y;
	w = bottom->x;
	h = bottom->y;
}

Rect::~Rect()
{
}

Rect::operator SDL_Rect*()
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}

bool Rect::Collide(Rect* r)
{
	return Collide(new Point(x, y)) && Collide(new Point(w, h));
}

bool Rect::Collide(Point* p)
{
	if ((p->x > x) && (p->x < x + w))
		if ((p->x > x) && (p->x < x + w))
			return true;
	return false;
}
