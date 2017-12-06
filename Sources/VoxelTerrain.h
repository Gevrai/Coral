#pragma once

#include "stdafx.h"

#include "Surface.h"
#include "Rect.h"
#include "Camera.h"

class VoxelTerrain
{
private:
	Surface* heightmap;
	Surface* colormap;

	bool _Create(Surface* heightmap, Surface* colormap);
	void _Destroy();
public:
	VoxelTerrain();
	VoxelTerrain(Surface* heightmap, Surface* colormap);
	~VoxelTerrain();

	bool Render(Surface surface, Camera camera);
};