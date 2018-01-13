#include "Camera.h"

Camera::Camera()
	: pos(Vec3D(0,0,0))
	, foward(Vec3D(1,0,0))
	, tilt(0.0)
{}

Camera::Camera(Vec3D pos, Vec3D foward, double tilt)
	: pos(pos)
	, foward(foward)
	, tilt(tilt)
{
	foward.normalize();
}

Vec3D Camera::getPos()    const { return pos; }
Vec3D Camera::getFoward() const { return foward; }
double Camera::getTilt()   const { return tilt; }

void Camera::setTilt(double _tilt) { tilt = _tilt; }
void Camera::setPos(Vec3D _pos) { pos = _pos; }

// FIXME this is hacky af
void Camera::rotateSideways(double ammount)
{
	foward.x = foward.x + ammount*foward.y;
	foward.y = foward.y - ammount*foward.x;
	foward.normalize();
}
