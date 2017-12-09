#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(Point* npos, int nheight, int nangle, int nhorizon, int ndistance)
{
	pos = npos;
	height = nheight;
	angle = nangle;
	horizon = nhorizon;
	distance = ndistance;
}


Camera::~Camera()
{
}
