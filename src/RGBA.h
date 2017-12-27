#pragma once

#include "stdafx.h"

class RGBA
{
public:
	Uint8 r, g, b, a;

	RGBA();
	RGBA(Uint32 rgba);
	RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255);
	~RGBA();

	void debugPrint();
};
