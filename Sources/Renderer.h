#pragma once

#include "Game.h"

class Renderer
{
protected:
	SDL_Renderer* renderer;

public:
	Renderer();
	RGBA* GetRGBA();
	bool SetRGBA(RGBA* color);
	SDL_BlendMode GetBlendMode();
	bool SetBlendMode(SDL_BlendMode mode);
	~Renderer();

	bool Draw(Rect* rect, bool full);
	bool Draw(Point* point);
};