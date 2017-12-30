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
	Uint16* yCurrentHeight = nullptr;

	Uint32 colormapW,colormapH, heightmapW, heightmapH;

	double resolutionDelta = 1.007;
	Uint32 drawDistance = 2000;
	double scaleHeight = 220.0;
	double fieldOfView = 90.0;

	// Resolution can be different for heightmap and colormap
	double heightmap_scalex;
	double heightmap_scaley;

	inline RGBA colormapPixelAt(double x, double y) const;
	inline Uint8 heightmapPixelAt(double x, double y) const;

public:
	VoxelTerrain(WindowRenderer* renderer, std::string mapname);
	~VoxelTerrain();

	bool loadMap(std::string mapname);

	double getHeightAt(double x, double j) const;

	void render(WindowRenderer* renderer, const Camera* camera) const;
};
