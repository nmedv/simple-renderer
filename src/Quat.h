#ifndef QUAT_H
#define QUAT_H

#include "Vec.h"


class Quat
{
public:
	Quat() {}
	Quat(const Quat& other) { w = other.w; x = other.x; y = other.y; z = other.z; }
	Quat(float angle, const Vec3f& axis) { makeRotate(angle, axis); }
	
	inline void setZero() { w = x = y = z = 0.0f; }
	inline float length2() const { return w*w + x*x + y*y + z*z; }
	
	void makeRotate(float angle, const Vec3f& axis);
	
	float w;
	float x;
	float y;
	float z;
};


#endif