#pragma once

#include "stdafx.h"

#include "Rect.h"
#include "RGBA.h"

class Surface
{
private:
	SDL_Surface* surface = nullptr;
	bool valid;

	bool _Lock();
	bool _Unlock();

	Uint32 _GetPixel(int x, int y);
	void _SetPixel(int x, int y, Uint32 pixel);

public:
	Surface();
	Surface(SDL_Surface*);
	Surface(int w, int h);
	Surface(Rect* rect);
	Surface(const std::string path);
	~Surface();

	SDL_Surface* getSDL_Surface();

	RGBA operator()(int x,int y);

	Uint32 width() const;
	Uint32 height() const;

	bool isValid() const;

	bool Fill(RGBA* pixel);
	bool FillRect(Rect* rect, RGBA* pixel);

	bool Blit(Surface* surface, Rect* src, Rect* dst);
	bool Blit(Surface* surface);

	Rect GetRect();

	bool Save(const char* path);
	bool Load(const char* path);

	RGBA GetRGBA(int x, int y);
};

