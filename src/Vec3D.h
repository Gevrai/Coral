#include <cmath>

class Vec3D {
 public:
	double x,y,z;
	Vec3D(double x, double y, double z);

	void operator()(double x, double y, double z);
	Vec3D operator*(double ammount) const;

	void normalize();
	void addInPlace(Vec3D that);
	void multInPlace(double ammount);

	double norm() const;
	double dot(Vec3D that) const;
	Vec3D cross(Vec3D that) const;
	double angleBetween(Vec3D that) const;
};
