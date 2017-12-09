#pragma once

#include "stdafx.h"

class RGBA
{
public:
	Uint8 r, g, b, a = 0;
	
	RGBA();
	RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a=0);
	~RGBA();

	operator Uint32();
};


