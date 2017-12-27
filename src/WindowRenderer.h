#pragma once

#include "stdafx.h"

#include "Surface.h"
#include "Rect.h"
#include "RGBA.h"

class WindowRenderer
{
private:
	Uint32 width, height;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

 public:
	WindowRenderer(std::string title, int w, int h, Uint32 x = SDL_WINDOWPOS_CENTERED, Uint32 y = SDL_WINDOWPOS_CENTERED, Uint32 flags = SDL_WINDOW_SHOWN);
	~WindowRenderer();

	void clear();
	void renderPresent();

	SDL_Renderer* getRenderer() const;
	SDL_Window* getWindow() const;

	SDL_BlendMode GetBlendMode();
	bool SetBlendMode(SDL_BlendMode mode);

	bool DrawRect(Rect rect, bool filled);
	bool DrawLine(RGBA color, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2);
	bool DrawPixel(RGBA color, Uint32 x, Uint32 y);
	bool DrawSurface(Surface* surface, Rect* positionRect);
};
