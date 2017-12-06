#pragma once

#include "stdafx.h"

#include "Point.h"
#include "Rect.h"

class Surface
{
private:
	SDL_Surface* surface = nullptr;

	bool _Create(int w, int h);
	bool _Destroy();

	bool _Lock();
	bool _Unlock();
	
	Uint32 _GetPixel(int x, int y);
	Uint32 _GetPixel(Point p);
	void _SetPixel(int x, int y, Uint32 pixel);

public:
	Surface();
	Surface(SDL_Surface*);
	Surface(int w, int h);
	Surface(Rect rect);
	Surface(const char* path);
	~Surface();

	Uint32 operator()(int x,int y);
	Uint32 operator()(Point p);

	operator SDL_Surface*();

	bool Fill(Uint8 r, Uint8 g, Uint8 b);
	bool Fill(Uint32 pixel);
	bool FillRect(Rect rect, Uint8 r, Uint8 g, Uint8 b);
	bool FillRect(Rect rect, Uint32 pixel);

	bool Blit(Surface surface, Rect src = Rect(), Rect dst = Rect());

	bool DrawVerticalLine(int x, int ytop, int ybottom, Uint32 color);

	Rect GetRect();

	int GetValue(int x, int y);
	int GetValue(Point p);

	bool Save(const char* path);
	bool Load(const char* path);
	
	Uint32 GetPixel(int x, int y);
	Uint32 GetPixel(Point p);
};

