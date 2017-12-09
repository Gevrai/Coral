#pragma once

#include "stdafx.h"

#include "Point.h"

	class Camera
	{
	public:
		Point* pos;
		int height, angle, horizon, distance = 0;

		Camera();
		Camera(Point* pos, int height, int angle, int horizon, int distance);
		~Camera();
	};
