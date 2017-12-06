#include "Game.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		Error(SDL_GetError());
}

Game::~Game()
{
	onQuit();
}

void Game::onQuit()
{
	SDL_Quit();
	exit(0);
}

bool Game::MainLoop()
{
	onStart();

	SDL_Event event;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				onQuit();
				break;

				//case SDL_APP_TERMINATING:

				//case SDL_APP_LOWMEMORY:

				// Focus Events? (untested) maybe mobile only
				/*case SDL_APP_WILLENTERBACKGROUND:
				case SDL_APP_DIDENTERBACKGROUND:
				case SDL_APP_WILLENTERFOREGROUND:
				case SDL_APP_DIDENTERFOREGROUND:*/

				// Window Events
				/*case SDL_WINDOWEVENT:
				case SDL_SYSWMEVENT:*/

				// Keyboard Events
				/*case SDL_KEYDOWN:
				case SDL_KEYUP:
				case SDL_TEXTEDITING:
				case SDL_TEXTINPUT:
				case SDL_KEYMAPCHANGED:*/

				// Mouse Events
				/*case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEWHEEL:*/

				// Joystick Events
				/*case SDL_JOYAXISMOTION:
				case SDL_JOYBALLMOTION:
				case SDL_JOYHATMOTION:
				case SDL_JOYBUTTONDOWN:
				case SDL_JOYBUTTONUP:
				case SDL_JOYDEVICEADDED:
				case SDL_JOYDEVICEREMOVED:*/

				// Gamepad Controllers Events
				/*case SDL_CONTROLLERAXISMOTION:
				case SDL_CONTROLLERBUTTONDOWN:
				case SDL_CONTROLLERBUTTONUP:
				case SDL_CONTROLLERDEVICEADDED:
				case SDL_CONTROLLERDEVICEREMOVED:
				case SDL_CONTROLLERDEVICEREMAPPED:*/

				// Mobile Stuff
				/*case SDL_FINGERDOWN:
				case SDL_FINGERUP:
				case SDL_FINGERMOTION:
				case SDL_DOLLARGESTURE:
				case SDL_DOLLARRECORD:
				case SDL_MULTIGESTURE:*/

				//case SDL_CLIPBOARDUPDATE:

				// Drag and Drop Events
				/*case SDL_DROPFILE:
				case SDL_DROPTEXT:
				case SDL_DROPBEGIN:
				case SDL_DROPCOMPLETE:*/

				// Audio device Event
				/*case SDL_AUDIODEVICEADDED:
				case SDL_AUDIODEVICEREMOVED:*/

				// Render Event
				/*case SDL_RENDER_TARGETS_RESET:
				case SDL_RENDER_DEVICE_RESET:*/

				// Custom Event
				//case SDL_USEREVENT:

			default:
				break;
			}
		}

		SDL_Delay(1000);
	}
	return true;
}

