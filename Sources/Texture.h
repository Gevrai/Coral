#pragma once

#include "Game.h"

class Texture
{
private:
	SDL_Texture* texture = nullptr;

public:
	Texture();
	Texture(SDL_Texture*);
	Texture(int w, int h);
	Texture(Rect* rect);
	Texture(const char* path);
	~Texture();

	RGBA* operator()(int x, int y);
	RGBA* operator()(Point* p);

	operator SDL_Texture*();

	bool Fill(RGBA* pixel);
	bool FillRect(Rect* rect, RGBA* pixel);

	bool Blit(Texture* texture, Rect* src, Rect* dst);
	bool Blit(Texture* texture);

	Rect* GetRect();

	bool Save(const char* path);
	bool Load(const char* path);

	RGBA* GetRGBA(int x, int y);
	RGBA* GetRGBA(Point* p);
};