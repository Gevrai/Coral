#pragma once

#include "stdafx.h"

#include "VoxelTerrain.h"
#include "WindowRenderer.h"
#include "Player.h"

#define MAX_FPS 60
#define WIDTH 800
#define HEIGHT 600

class Game
{
 private:
	std::string title;
	bool isRunning;
	double deltaTime = 1.0 / MAX_FPS;

	WindowRenderer* windowRenderer = nullptr;
	VoxelTerrain* voxelTerrain = nullptr;
	Player* player = nullptr;

 public:
	Game(std::string title);
	~Game();

	int run();
	bool init();
	void quit();
	void mainLoop();

	void handleEvents();
	void renderAll();
};
