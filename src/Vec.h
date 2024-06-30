#ifndef VEC_H
#define VEC_H

#include "Utils.h"

#include <cmath>
#include <iostream>


// a three-dimensional vector of the float type
class Vec3f
{
public:
	Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
	Vec3f() : x(0), y(0), z(0) {};
	
	inline bool operator == (const Vec3f& vec) const
	{
		return x == vec.x && y == vec.y && z == vec.z;
	}
	
	inline float length() const { return sqrt(x*x + y*y + z*z); }
	inline void normalize() { float l = length(); x /= l; y /= l; z /= l; }

	float x;
	float y;
	float z;
};


const Vec3f X_AXIS = Vec3f(1.0f, 0.0f, 0.0f);
const Vec3f Y_AXIS = Vec3f(0.0f, 1.0f, 0.0f);
const Vec3f Z_AXIS = Vec3f(0.0f, 0.0f, 1.0f);


// a three-dimensional vector of the float type with an additional homogeneous
// coordinate for multiplication by 4x4 matrices
class Vec4f
{
public:
	Vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
	Vec4f() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {};

	float x;
	float y;
	float z;
	float w;
};


#endif