#pragma once

#include "stdafx.h"

#include "Vec3D.h"

class Camera
{
 private:
	Vec3D pos, up, foward;

 public:
	Camera();
  Camera(Vec3D pos, Vec3D up, Vec3D foward);
	~Camera();

	Vec3D getPos() const;
	Vec3D getUp() const;
	Vec3D getFoward() const;

	void moveFoward(double ammount);
	void moveUp(double ammount);
	void rotateSideways(double ammount);
};
