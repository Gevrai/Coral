#include "Window.h"

Window::Renderer::Renderer()
{
}

Window::Renderer::Renderer(SDL_Window* window)
{
	// Accelarated renderer because why not?
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Color* Window::Renderer::GetColor()
{
	Color* color = new Color();
	if (SDL_GetRenderDrawColor(renderer, &color->r, &color->g, &color->b, &color->a) < 0)
	{
		return nullptr;
	};
	return color;
}

bool Window::Renderer::SetColor(Color* color)
{
	if( SDL_GetRenderDrawColor(renderer, &color->r, &color->g, &color->b, &color->a) < 0)
	{
		return false;
	}
	return true;
}

SDL_BlendMode Window::Renderer::GetBlendMode()
{
	SDL_BlendMode mode;
	if (SDL_GetRenderDrawBlendMode(renderer, &mode) < 0)
	{
		return SDL_BLENDMODE_INVALID;
	}
	return mode;
}

bool Window::Renderer::SetBlendMode(SDL_BlendMode mode)
{
	if (SDL_SetRenderDrawBlendMode(renderer, mode) < 0)
		return false;
	return true;
}

bool Window::Renderer::Draw(Point* point)
{
	if (SDL_RenderDrawPoint(renderer, point->x, point->y) < 0)
		return false;
	return true;
}

bool Window::Renderer::Draw(Rect* rect, bool full)
{
	if (full)
	{
		if (SDL_RenderFillRect(renderer, *rect) < 0)
			return false;
		return true;
	}
	if (SDL_RenderDrawRect(renderer, *rect) < 0)
		return false;
	return true;
}

Window::Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}
