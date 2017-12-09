#pragma once

#include "stdafx.h"

#include "Surface.h"
#include "Point.h"
#include "Rect.h"
#include "RGBA.h"

class Window
{
private:

	SDL_Window* window = nullptr;

	bool _Create(const char* title, int x, int y, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	bool _Create(const char* title, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	void _Destroy();

	class Renderer
	{
	private:
		SDL_Renderer* renderer;

	public:
		Renderer();
		Renderer(SDL_Window* window);
		RGBA* GetRGBA();
		bool SetRGBA(RGBA* color);
		SDL_BlendMode GetBlendMode();
		bool SetBlendMode(SDL_BlendMode mode);
		~Renderer();

		bool Draw(Rect* rect, bool full);
		bool Draw(Point* point);
	};

public:
	Rect* rect;
	Renderer* renderer =nullptr;

	Window();
	Window(const char* title, int x, int y, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	Window(const char* title, Rect* rect, Uint32 flags = SDL_WINDOW_SHOWN);
	Window(const char* title, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN);
	Window(const char* title, Point* point, Uint32 flags = SDL_WINDOW_SHOWN);
	~Window();
	
	//bool Draw();
};

