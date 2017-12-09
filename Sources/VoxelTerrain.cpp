#include "VoxelTerrain.h"

bool VoxelTerrain::_Create(Surface* pheightmap, Surface* pcolormap)
{
	heightmap = pheightmap;
	colormap = pcolormap;
	__debugbreak();
	return true;
}

void VoxelTerrain::_Destroy()
{
}

VoxelTerrain::VoxelTerrain()
{
}

VoxelTerrain::VoxelTerrain(Surface* pheightmap, Surface* pcolormap)
{
	
	_Create(pheightmap, pcolormap);
	__debugbreak();
}

VoxelTerrain::~VoxelTerrain()
{
	_Destroy();
}


/*Surface* VoxelTerrain::Render(Surface surface, Point p, int height, int horizon, int scale_height, int distance)
{
	//#TODO clean this
	int screen_width = surface.GetWidth();
	int screen_height = surface.GetHeight();

	Uint32 debug = 0;
	
	int dx;
	Point pleft, pright;
	for (int z = distance; z > 0; z--)
	{
		// Find line on map.
		pleft = Point(-z + p.x, -z + p.y);
		pright = Point(z + p.x, -z + p.y);

		// Segment the line
		dx = (pright.x - pleft.x) / screen_width;

		//Raster and draw rect for each segments
		for (int x = 0; x < screen_width; x++)
		{
			//#TODO FIX THIS
			//__debugbreak();

			debug = heightmap.GetValue(pleft);

			__debugbreak();

			int position = (height - heightmap.GetValue(pleft)) / z * scale_height + horizon;
			surface.FillRect(Rect(x, position, x, height), colormap(pleft));
			pleft.x += dx;
		}
	}
	return surface;
}*/

bool VoxelTerrain::Render(Window* window, Camera* camera)
{
	Rect* period = colormap->GetRect();
	Rect* screen = window->rect;
	period->w -= 1;
	period->h -= 1;

	float sinang = sin(camera->angle);
	float cosang = (camera->angle);

	int *hiddeny = new int[screen->w];
	for (int i = 0; i < screen->w; i++)
		hiddeny[i] = screen->h;

	float plx, ply, prx, pry = 0;
	float dx, dy = 0;
	float dz = 1.;

	float invz, heightonscreen = NULL;

	// Draw from front to back
	for (int z = 1; z < camera->distance; z += dz)
	{
		// 90 degree field of view
		plx = -cosang * z - sinang * z;
		ply = sinang * z - cosang * z;
		prx = cosang * z - sinang * z;
		pry = -sinang * z - cosang * z;

		dx = (prx - plx) / screen->w;
		dy = (pry - ply) / screen->w;
		plx += camera->pos->x;
		ply += camera->pos->y;
		invz = 1. / z * 240.;
		for (int i = 0; i < screen->w; i = i + 1)
		{
			Point* offset = new Point((int)ply & period->w, (int)plx & period->h);
			//heightonscreen = (camera->height - heightmap->GetValue(offset) * invz + camera->horizon);
			//surface->DrawVerticalLine(i, heightonscreen, hiddeny[i], colormap->GetPixel(offset));
			if (heightonscreen < hiddeny[i]) hiddeny[i] = heightonscreen;
			plx += dx;
			ply += dy;
		}
	}
	dz += 0.01;
	return false;
}