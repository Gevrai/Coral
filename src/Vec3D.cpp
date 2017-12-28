#include "Vec3D.h"

Vec3D::Vec3D(double x, double y, double z)
	: x(x), y(y), z(z)
{}

void Vec3D::operator()(double _x, double _y, double _z) {
	x = _x; y = _y; z = _z;
}

Vec3D Vec3D::operator*(double ammount) const {
	return Vec3D(x*ammount, y*ammount, z*ammount);
}

void Vec3D::addInPlace(Vec3D that)
{
	x += that.x; y += that.y; z += that.z;
}

void Vec3D::multInPlace(double ammount)
{
	x *= ammount; y *= ammount; z *= ammount;
}

void Vec3D::normalize()
{
	//Cannot normalize a nil vector
	if (x == 0.0 && y == 0.0 && z == 0.0)
		return;
	double norm = this->norm();
	x /= norm;
	y /= norm;
	z /= norm;
}

double Vec3D::norm() const
{
	return std::sqrt(x*x + y*y + z*z);
}

double Vec3D::dot(Vec3D that) const
{
	return x*that.x + y*that.y + z*that.z;
}

Vec3D Vec3D::cross(Vec3D that) const
{
	return Vec3D(y*that.z - z*that.y,
							 z*that.x - x*that.z,
							 x*that.y - y*that.x);
}

double Vec3D::angleBetween(Vec3D that) const
{
		return std::acos(this->dot(that) / (this->norm() * that.norm()));
}
