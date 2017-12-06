#include "Game.h"

// #TODO figure out the right way to make a main object
int main(int argc, char* args[])	
{
	Game VoxelSpace;
	//return VoxelSpace.MainLoop();

	Surface colormap("Assets/colormap.bmp");
	Surface heightmap("Assets/heightmap.bmp");

	Window window("Test", 800, 600);

	__debugbreak();

	VoxelTerrain terrain(&colormap, &heightmap);

	__debugbreak();

	Camera camera(Point(0,0), 50, 120, 120, 300);

	__debugbreak();

	terrain.Render(window.surface, camera);

	__debugbreak();

	window.Draw();
	return VoxelSpace.MainLoop();
}