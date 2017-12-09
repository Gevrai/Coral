#pragma once

#include "stdafx.h"

class Color
{
public:
	Uint8 r, g, b, a = 0;
	
	Color();
	Color(Uint8 r,Uint8 b,Uint8 g,Uint8 a=0);
	~Color();
};

