#include "Window.h"

bool Window::_Create(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	window = SDL_CreateWindow(title, x, y, w, h, flags);
	if (window)
	{
		surface = Surface(SDL_GetWindowSurface(window));
		return true;
	}
	return false;
}

bool Window::_Create(const char * title, int w, int h, Uint32 flags)
{
	return _Create(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
}

void Window::_Destroy()
{
	SDL_DestroyWindow(window);
}

Window::Window()
{
}

Window::Window(const char * title, int x, int y, int w, int h, Uint32 flags)
{

}

Window::Window(const char * title, Rect rect, Uint32 flags)
{
	__debugbreak();
	_Create(title, rect.w, rect.h, flags);
	__debugbreak();
}

Window::Window(const char * title, int w, int h, Uint32 flags)
{
	_Create(title, w, h, flags);
}

Window::Window(const char * title, Point point, Uint32 flags)
{
	_Create(title, point.x, point.y, flags);
}

Window::~Window()
{
	_Destroy();
}

bool Window::Draw()
{
	if (SDL_UpdateWindowSurface(window) < 0)
		return false;
	return true;
}