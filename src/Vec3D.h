#include <cmath>

class Vec3D {
 public:
	double x,y,z;
	Vec3D(double x, double y, double z);

	void normalize();
	double norm() const;
	double dot(Vec3D that) const;
	Vec3D cross(Vec3D that) const;
	double angleBetween(Vec3D that) const;
};
