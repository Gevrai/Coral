#include "Renderer.h"

Renderer::Renderer()
{
}

RGBA* Renderer::GetRGBA()
{
	RGBA* color = new RGBA();
	if (SDL_GetRenderDrawColor(renderer, &color->r, &color->g, &color->b, &color->a) < 0)
	{
		return nullptr;
	};
	return color;
}

bool Renderer::SetRGBA(RGBA* color)
{
	if( SDL_GetRenderDrawColor(renderer, &color->r, &color->g, &color->b, &color->a) < 0)
	{
		return false;
	}
	return true;
}

SDL_BlendMode Renderer::GetBlendMode()
{
	SDL_BlendMode mode;
	if (SDL_GetRenderDrawBlendMode(renderer, &mode) < 0)
	{
		return SDL_BLENDMODE_INVALID;
	}
	return mode;
}

bool Renderer::SetBlendMode(SDL_BlendMode mode)
{
	if (SDL_SetRenderDrawBlendMode(renderer, mode) < 0)
		return false;
	return true;
}

bool Renderer::Draw(Point* point)
{
	if (SDL_RenderDrawPoint(renderer, point->x, point->y) < 0)
		return false;
	return true;
}

bool Renderer::Draw(Rect* rect, bool full)
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

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}
