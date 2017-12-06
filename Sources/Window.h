#pragma once

#include "stdafx.h"

#include "Surface.h"
#include "Point.h"
#include "Rect.h"

class Window
{
private:
	SDL_Window* window = nullptr;

	bool _Create(const char* title, int x, int y, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	bool _Create(const char* title, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	void _Destroy();
	
public:
	Surface surface;

	Window();
	Window(const char* title, int x, int y, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	Window(const char* title, Rect rect, Uint32 flags = SDL_WINDOW_SHOWN);
	Window(const char* title, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	Window(const char* title, Point point, Uint32 flags = SDL_WINDOW_SHOWN);
	~Window();
	
	bool Draw();
};

