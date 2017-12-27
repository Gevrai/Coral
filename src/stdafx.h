#pragma once

// Standard Lib
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <exception>
#include <iostream>

// SDL Lib
#include <SDL.h>
#include <SDL_image.h>

constexpr bool VERBOSE = true;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MOD(a,b) (((a)%(b)+(b))%(b))

#define ERROR(error) printf("%s:%d>%s\n", __FILE__, __LINE__, error);
#define PRINT_SDL_ERROR(error) {printf("%s\n-> SDL_Error : %s\n", error, SDL_GetError());}
#define PRINT_IMG_ERROR(error) {printf("%s\n-> IMG_Error : %s\n", error, IMG_GetError());}
#define PRINT_VERBOSE(msg) { if (VERBOSE) printf(msg); }

class InitializationException: public std::exception { };
