#include "WindowRenderer.h"

WindowRenderer::WindowRenderer(const std::string title, int w, int h, Uint32 x ,Uint32 y, Uint32 flags)
	: width(w) , height(h)
{
	// Create window
	window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if (window == nullptr) {
		PRINT_SDL_ERROR("Could not create window!");
		throw InitializationException();
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		PRINT_SDL_ERROR("Could not create renderer!");
		throw InitializationException();
	}
	SDL_RenderSetLogicalSize(renderer, w, h);
}

WindowRenderer::~WindowRenderer()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

SDL_Renderer* WindowRenderer::getRenderer() const { return renderer; }
SDL_Window* WindowRenderer::getWindow() const { return window; }

void WindowRenderer::clear()
{
	SDL_SetRenderDrawColor(renderer,50,50,255,255);
	SDL_RenderClear(renderer);
}

void WindowRenderer::renderPresent()
{
	SDL_RenderPresent(renderer);
}

SDL_BlendMode WindowRenderer::GetBlendMode()
{
	SDL_BlendMode mode;
	if (SDL_GetRenderDrawBlendMode(renderer, &mode) < 0)
	{
		return SDL_BLENDMODE_INVALID;
	}
	return mode;
}

bool WindowRenderer::SetBlendMode(SDL_BlendMode mode)
{
	return (SDL_SetRenderDrawBlendMode(renderer, mode) >= 0);
}

bool WindowRenderer::DrawLine(RGBA color, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2) {
	return
		(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) >= 0)
		&& (SDL_RenderDrawLine(renderer, x1, y1, x2, y2) >= 0);
}

bool WindowRenderer::DrawPixel(RGBA color, Uint32 x, Uint32 y)
{
	return
		(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) >= 0)
		&& (SDL_RenderDrawPoint(renderer, x, y) >= 0);
}

bool WindowRenderer::DrawRect(Rect rect, bool filled)
{
	SDL_Rect sdlrect = rect.getSDL_Rect();
	if (filled)
		return (SDL_RenderFillRect(renderer, &sdlrect) >= 0);
	else
		return (SDL_RenderDrawRect(renderer, &sdlrect) >= 0);
}

bool WindowRenderer::DrawSurface(Surface* surface, Rect* positionRect)
{
	SDL_Rect sdlrect;
	int result;
	SDL_Surface* sdlsurface = surface->getSDL_Surface();
	SDL_Texture* sdltexture = SDL_CreateTextureFromSurface(renderer, sdlsurface);
	if (sdltexture == nullptr)
		return false;
	if (positionRect != NULL){
		sdlrect = positionRect->getSDL_Rect();
		result = SDL_RenderCopyEx(renderer, sdltexture, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
	}
	else {
		result = SDL_RenderCopyEx(renderer, sdltexture, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
	}
	SDL_DestroyTexture(sdltexture);
	return result != -1;
}
