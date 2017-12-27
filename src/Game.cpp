#include "Game.h"

Game::Game(std::string title)
	: title(title)
	, isRunning(false)
{}

Game::~Game()
{
	if (windowRenderer) delete windowRenderer;
	if (voxelTerrain)   delete voxelTerrain;
	if (playerCamera)   delete playerCamera;
	IMG_Quit();
	SDL_Quit();
}

bool Game::init()
{
	isRunning = false;

	// Initialize SDL subsystems
	PRINT_VERBOSE("Setting up SDL...");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		PRINT_SDL_ERROR("Could not initialize SDL!");
		return false;
	}
	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		PRINT_SDL_ERROR("Could not initialize SDL_Image!)");
		return false;
	}
	PRINT_VERBOSE("Done.\n");

	PRINT_VERBOSE("Setting up game entities...");
	// Create window renderer and terrain
	try {
		windowRenderer = new WindowRenderer(title, WIDTH, HEIGHT);
		voxelTerrain = new VoxelTerrain(windowRenderer, "9.png");
		playerCamera = new Camera(Vec3D(0,0,150), Vec3D(0,0,1), Vec3D(0,1,0));
	} catch (InitializationException& e) {
		// Abort
		if (windowRenderer) delete windowRenderer;
		if (voxelTerrain) delete voxelTerrain;
		if (playerCamera) delete playerCamera;
		return false;
	}
	PRINT_VERBOSE("Done.\n");

	// All is ready to run
	isRunning = true;
	return true;
}

int Game::run()
{
	if(!init())
		return -1;
	mainLoop();
	return 0;
}

void Game::quit()
{
	isRunning = false;
}

void Game::renderAll()
{
	windowRenderer->clear();
	voxelTerrain->render(windowRenderer, playerCamera);
	windowRenderer->renderPresent();
}

/* Print all information about a key event */
void PrintKeyInfo( SDL_KeyboardEvent *key ){
	/* Is it a release or a press? */
	if( key->type == SDL_KEYUP )
		printf( "Release:- " );
	else
		printf( "Press:- " );

	/* Print the hardware scancode first */
	printf( "Scancode: 0x%02X", key->keysym.scancode );
	/* Print the name of the key */
	printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
	/* We want to print the unicode info, but we need to make */
	/* sure its a press event first (remember, release events */
	/* don't have unicode info                                */
	if( key->type == SDL_KEYDOWN ){
		/* If the Unicode value is less than 0x80 then the    */
		/* unicode value can be used to get a printable       */
		/* representation of the key, using (char)unicode.    */
	}
	printf( "\n" );
}


void Game::mainLoop()
{
	Uint32 loopStartTime;
	Uint32 frameDuration = 1000/MAX_FPS;
	SDL_Event event;

	bool keyW, keyA, keyS, keyD, keyE, keyQ;
	keyW=keyA=keyS=keyD=keyE=keyQ=false;

	const Uint8 W = 0x1A;
	const Uint8 A = 0x04;
	const Uint8 S = 0x16;
	const Uint8 D = 0x07;
	const Uint8 E = 0x08;
	const Uint8 Q = 0x14;

	while (isRunning)
		{
			if (VERBOSE) printf("FPS: %d\n", 1000/frameDuration);

			loopStartTime = SDL_GetTicks();

			// Simple event handler
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					return quit();
				case SDL_KEYDOWN:
					switch( event.key.keysym.scancode ){
					case W: keyW = true; break;
					case A: keyA = true; break;
					case S: keyS = true; break;
					case D: keyD = true; break;
					case E: keyE = true; break;
					case Q: keyQ = true; break;
					default: PrintKeyInfo(&event.key); break;
					}
					break;
				case SDL_KEYUP:
					switch( event.key.keysym.scancode ){
					case W: keyW = false; break;
					case A: keyA = false; break;
					case S: keyS = false; break;
					case D: keyD = false; break;
					case E: keyE = false; break;
					case Q: keyQ = false; break;
					default: break;
					}
					break;
				default:
					break;
				}
			}

			// Move camera
			if(keyW) playerCamera->moveFoward(100.0 * deltaTime);
			if(keyS) playerCamera->moveFoward(-100.0 * deltaTime);
			if(keyA) playerCamera->rotateSideways(-1.0 * deltaTime);
			if(keyD) playerCamera->rotateSideways(1.0 * deltaTime);
			if(keyE) playerCamera->moveUp(100.0 * deltaTime);
			if(keyQ) playerCamera->moveUp(-100.0 * deltaTime);

			renderAll();

			// Framerate calculations
			frameDuration = SDL_GetTicks() - loopStartTime;
			if( frameDuration < 1000/MAX_FPS) {
				deltaTime = 1000.0/ MAX_FPS;
				SDL_Delay(1000/MAX_FPS - frameDuration);
			} else {
				deltaTime = (double) frameDuration / 1000.0;
			}
		}
}
