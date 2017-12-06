#pragma once

#include "stdafx.h"

#include "Point.h"

	class Rect
	{
	public:
		int x, y, w, h = 0;
		Rect();
		Rect(int x, int y, int w, int h);
		Rect(SDL_Rect rect);
		Rect(Point top, Point bottom);
		~Rect();

		operator SDL_Rect*();

		bool Collide(Rect r);
		bool Collide(Point p);
	};