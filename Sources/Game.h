#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Point.h"
#include "Rect.h"
#include "Renderer.h"
#include "Surface.h"
#include "VoxelTerrain.h"
#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	bool onStart();
	void onQuit();
	bool MainLoop();
};