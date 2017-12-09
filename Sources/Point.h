#pragma once

#include "stdafx.h"

class Point
{
public:
	int x, y = 0;

	Point();
	Point(int x, int y);
	~Point();

	Point operator +(Point*);
	Point operator +(int);
	Point operator -(Point*);
	Point operator -(int);
	Point operator /(Point*);
	Point operator /(int);
	Point operator *(Point*);
	Point operator *(int);

	operator SDL_Point*();
};