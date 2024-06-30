#include "Quat.h"

#include <cmath>


void Quat::makeRotate(float angle, const Vec3f& axis)
{
	// Source: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

	float length = axis.length();
	if (length < 0.0000001f)
		return setZero();
	
	float inverse_length = 1 / length;
	float coshalfangle = cosf(0.5f * angle);
	float sinhalfangle = sinf(0.5f * angle);
	
	w = coshalfangle;
	x = axis.x * inverse_length * sinhalfangle;
	y = axis.y * inverse_length * sinhalfangle;
	z = axis.z * inverse_length * sinhalfangle;
}