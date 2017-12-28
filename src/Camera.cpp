#include "Camera.h"

Camera::Camera()
	: pos(Vec3D(0,0,0))
	, up(Vec3D(0,0,1))
	, foward(Vec3D(1,0,0))
{}

Camera::Camera(Vec3D pos, Vec3D up, Vec3D foward)
	: pos(pos)
	, up(up)
	, foward(foward)
{
	up.normalize();
	foward.normalize();
}

Vec3D Camera::getPos()    const { return pos; }
Vec3D Camera::getUp()     const { return up; }
Vec3D Camera::getFoward() const { return foward; }

void Camera::setPos(Vec3D _pos) { pos = _pos; }

Camera::~Camera()
{
}

void Camera::rotateSideways(double ammount)
{
	foward.x = foward.x + ammount*foward.y;
	foward.y = foward.y - ammount*foward.x;
	foward.normalize();
}
