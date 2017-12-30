#include "Game.h"

Game::Game(std::string title)
	: title(title)
	, isRunning(false)
{}

Game::~Game()
{
	if (windowRenderer) delete windowRenderer;
	if (voxelTerrain)   delete voxelTerrain;
	if (player)         delete player;
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
		voxelTerrain = new VoxelTerrain(windowRenderer, "7.png");
		player = new Player(PLAYER_INIT_POSITION);
	} catch (InitializationException& e) {
		// Abort
		if (windowRenderer) delete windowRenderer;
		if (voxelTerrain) delete voxelTerrain;
		if (player) delete player;
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
	voxelTerrain->render(windowRenderer, player->getCamera());
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

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return quit();
		case SDL_KEYDOWN:
			switch( event.key.keysym.scancode ){
			case KEY_W: player->startAction(FOWARD); break;
			case KEY_A: player->startAction(TURN_LEFT); break;
			case KEY_S: player->startAction(BACKWARD); break;
			case KEY_D: player->startAction(TURN_RIGHT); break;
			case KEY_E: player->startAction(UP); break;
			case KEY_Q: player->startAction(DOWN); break;
			default: PrintKeyInfo(&event.key); break;
			}
			break;
		case SDL_KEYUP:
			switch( event.key.keysym.scancode ){
			case KEY_W: player->stopAction(FOWARD); break;
			case KEY_A: player->stopAction(TURN_LEFT); break;
			case KEY_S: player->stopAction(BACKWARD); break;
			case KEY_D: player->stopAction(TURN_RIGHT); break;
			case KEY_E: player->stopAction(UP); break;
			case KEY_Q: player->stopAction(DOWN); break;
			default: break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::mainLoop()
{
	Uint32 loopStartTime;
	Uint32 frameDuration = 1000/MAX_FPS;

	while (isRunning)
		{
			if (VERBOSE) printf("FPS: %d\n", 1000/frameDuration);

			loopStartTime = SDL_GetTicks();

			handleEvents();

			player->update(deltaTime);
			player->checkCollision(voxelTerrain);

			renderAll();

			// Framerate calculations
			frameDuration = SDL_GetTicks() - loopStartTime;
			if( frameDuration < 1000/MAX_FPS) {
				deltaTime = 1000.0 / MAX_FPS;
				SDL_Delay(1000/MAX_FPS - frameDuration);
			} else {
				deltaTime = (double) frameDuration / 1000.0;
			}
		}
}
