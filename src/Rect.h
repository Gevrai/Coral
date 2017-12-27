#pragma once

#include "stdafx.h"

class Rect
{
public:
	int x, y, w, h;
	Rect();
	Rect(int x, int y, int w, int h);
	Rect(const SDL_Rect &rect);

	SDL_Rect getSDL_Rect();

	bool Collide(const Rect &r);
};
