#pragma once

#include "stdafx.h"

#include "Point.h"
#include "Rect.h"
#include "RGBA.h"

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
	Surface(Rect* rect);
	Surface(const char* path);
	~Surface();

	RGBA* operator()(int x,int y);
	RGBA* operator()(Point* p);

	operator SDL_Surface*();

	bool Fill(RGBA* pixel);
	bool FillRect(Rect* rect, RGBA* pixel);

	bool Blit(Surface* surface, Rect* src, Rect* dst);
	bool Blit(Surface* surface);

	Rect* GetRect();

	bool Save(const char* path);
	bool Load(const char* path);
	
	RGBA* GetRGBA(int x, int y);
	RGBA* GetRGBA(Point* p);
};

