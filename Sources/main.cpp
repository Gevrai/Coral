#include "Game.h"

// #TODO figure out the right way to make a main object
int main(int argc, char* args[])	
{
	__debugbreak();
	Game VoxelSpace;

	__debugbreak();

	Surface* colormap = new Surface("Assets/colormap.bmp");
	Surface* heightmap = new Surface("Assets/heightmap.bmp");

	__debugbreak();

	Window* window = new Window("Test", 800, 600);

	__debugbreak();

	//VoxelTerrain terrain(colormap, heightmap);

	__debugbreak();

	Camera* camera = new Camera(new Point(0,0), 50, 120, 120, 300);

	__debugbreak();

	//window->surface->Blit(terrain.Render(window->surface, camera));

	__debugbreak();


	return VoxelSpace.MainLoop();
}