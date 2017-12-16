#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(SDL_Texture *)
{
}

Texture::Texture(int w, int h)
{
}

Texture::Texture(Rect * rect)
{
}

Texture::Texture(const char * path)
{
}

Texture::~Texture()
{
}

RGBA * Texture::operator()(int x, int y)
{
	return nullptr;
}

RGBA * Texture::operator()(Point * p)
{
	return nullptr;
}

Texture::operator SDL_Texture*()
{
}

bool Texture::Fill(RGBA * pixel)
{
	return false;
}

bool Texture::FillRect(Rect * rect, RGBA * pixel)
{
	return false;
}

bool Texture::Blit(Texture * texture, Rect * src, Rect * dst)
{
	return false;
}

bool Texture::Blit(Texture * texture)
{
	return false;
}

Rect * Texture::GetRect()
{
	return nullptr;
}

bool Texture::Save(const char * path)
{
	return false;
}

bool Texture::Load(const char * path)
{
	return false;
}

RGBA * Texture::GetRGBA(int x, int y)
{
	return nullptr;
}

RGBA * Texture::GetRGBA(Point * p)
{
	return nullptr;
}
