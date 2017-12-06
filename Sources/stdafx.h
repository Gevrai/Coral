#pragma once

// Standard Lib
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// SDL Lib
#include <SDL.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define Error(error) printf("%s:%d>%s\n", __FILE__, __LINE__, error);