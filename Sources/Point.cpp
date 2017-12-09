#include "Point.h"

Point::Point()
{
}

Point::Point(int nx, int ny)
{
	x = nx;
	y = ny;
}

Point::~Point()
{
}

Point Point::operator+(Point* p)
{
	return Point(x+p->x,y+p->y);
}

Point Point::operator+(int n)
{
	return Point(x+n,y+n);
}

Point Point::operator-(Point* p)
{
	return Point(x-p->x,y-p->y);
}

Point Point::operator-(int n)
{
	return Point(x-n,y-n);
}

Point Point::operator/(Point* p)
{
	return Point(x/p->x,y/p->y);
}

Point Point::operator/(int n)
{
	return Point(x / n, y / n);
}

Point Point::operator*(Point* p)
{
	return Point(x * p->x, y * p->y);
}

Point Point::operator*(int n)
{
	return Point(x * n, y * n);
}

Point::operator SDL_Point*()
{
	SDL_Point* point = new SDL_Point();
	point->x = x;
	point->y = y;
	return point;
}
