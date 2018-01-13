#pragma once

#include "stdafx.h"

#include "Vec3D.h"

class Camera
{
 private:
	Vec3D pos, foward;
	double tilt;

 public:
	Camera();
  Camera(Vec3D pos, Vec3D foward, double tilt);

	Vec3D getPos() const;
	Vec3D getFoward() const;
	double getTilt() const;

	void setPos(Vec3D pos);
	void setTilt(double _tilt);

	void rotateSideways(double ammount);
};
