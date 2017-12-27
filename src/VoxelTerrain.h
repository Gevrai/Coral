#pragma once

#include "stdafx.h"

#include "Surface.h"
#include "Rect.h"
#include "Camera.h"
#include "WindowRenderer.h"

class VoxelTerrain
{
private:
	Uint8* heightmap = nullptr;
	RGBA* colormap = nullptr;

	Uint32 colormapW,colormapH, heightmapW, heightmapH;

	Uint32 horizon = 100;
	Uint32 drawDistance = 1500;
	double scaleHeight = 150.0;

	// Resolution can be different for heightmap and colormap
	double heightmap_scalex;
	double heightmap_scaley;

	inline RGBA colormapPixelAt(double x, double y);
	inline Uint8 heightmapPixelAt(double x, double y);

public:
	VoxelTerrain(WindowRenderer* renderer, std::string mapname);
	~VoxelTerrain();

	bool loadMap(std::string mapname);

	void render(WindowRenderer* renderer, Camera* camera);
};
