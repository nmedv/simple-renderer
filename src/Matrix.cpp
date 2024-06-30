#include "Matrix.h"
#include "Quat.h"

#include <cmath>


#define SET_ROW(row, a1, a2, a3, a4) \
	_mat[(row)][0] = (a1); \
	_mat[(row)][1] = (a2); \
	_mat[(row)][2] = (a3); \
	_mat[(row)][3] = (a4);
	
#define INNER_PRODUCT(mat1, mat2, row, col) \
	(mat1)._mat[(row)][0] * (mat2)._mat[0][(col)] + \
	(mat1)._mat[(row)][1] * (mat2)._mat[1][(col)] + \
	(mat1)._mat[(row)][2] * (mat2)._mat[2][(col)] + \
	(mat1)._mat[(row)][3] * (mat2)._mat[3][(col)]


Vec4f Matrixf::operator * (const Vec4f& vec) const
{
	return Vec4f(
		_mat[0][0] * vec.x + _mat[0][1] * vec.y + _mat[0][2] * vec.z + _mat[0][3] * vec.w,
		_mat[1][0] * vec.x + _mat[1][1] * vec.y + _mat[1][2] * vec.z + _mat[1][3] * vec.w,
		_mat[2][0] * vec.x + _mat[2][1] * vec.y + _mat[2][2] * vec.z + _mat[2][3] * vec.w,
		_mat[3][0] * vec.x + _mat[3][1] * vec.y + _mat[3][2] * vec.z + _mat[3][3] * vec.w
	);
}


void Matrixf::postMult(const Matrixf& mat)
{
	for (int row = 0; row < 4; row++)
	{
		SET_ROW(row,
			INNER_PRODUCT(*this, mat, row, 0),
			INNER_PRODUCT(*this, mat, row, 1),
			INNER_PRODUCT(*this, mat, row, 2),
			INNER_PRODUCT(*this, mat, row, 3))
	}
}


void Matrixf::mult(const Matrixf& m1, const Matrixf& m2)
{
	for (int row = 0; row < 4; row++)
	{
		SET_ROW(row,
			INNER_PRODUCT(m1, m2, row, 0),
			INNER_PRODUCT(m1, m2, row, 1),
			INNER_PRODUCT(m1, m2, row, 2),
			INNER_PRODUCT(m1, m2, row, 3))
	}
}


void Matrixf::makeIdentity()
{
	SET_ROW(0,  1.0f, 0.0f, 0.0f, 0.0f)
	SET_ROW(1,  0.0f, 1.0f, 0.0f, 0.0f)
	SET_ROW(2,  0.0f, 0.0f, 1.0f, 0.0f)
	SET_ROW(3,  0.0f, 0.0f, 0.0f, 1.0f)
}


void Matrixf::makeTranslate(const Vec3f& vec)
{
	SET_ROW(0,  1.0f, 0.0f, 0.0f, vec.x)
	SET_ROW(1,  0.0f, 1.0f, 0.0f, vec.y)
	SET_ROW(2,  0.0f, 0.0f, 1.0f, vec.z)
	SET_ROW(3,  0.0f, 0.0f, 0.0f,  1.0f)
}


void Matrixf::makeRotate(float angle, const Vec3f& axis)
{
	// Source: https://en.wikipedia.org/wiki/Rotation_matrix#Quaternion

	Quat quat = Quat(angle, axis);
	
	float rlength2;
	float length2 = quat.length2();
	if (length2 != 1.0f)
		rlength2 = 2.0f / length2;
	else
		rlength2 = 2.0f;

	float x2, y2, z2, xx, xy, xz, yy, yz, zz, wx, wy, wz;
	
	x2 = rlength2 * quat.x;
	y2 = rlength2 * quat.y;
	z2 = rlength2 * quat.z;
	
	xx = quat.x * x2;
	xy = quat.x * y2;
	xz = quat.x * z2;
	
	yy = quat.y * y2;
	yz = quat.y * z2;
	zz = quat.z * z2;
	
	wx = quat.w * x2;
	wy = quat.w * y2;
	wz = quat.w * z2;
	
	// The matrix is inverted relative to the main diagonal because we use the
	// RHS expression to transform column vectors
	SET_ROW(0,  1.0f-yy-zz,       xy+wz,       xz+wy,  0.0f)
	SET_ROW(1,       xy-wz,  1.0f-xx-zz,       yz+wx,  0.0f)
	SET_ROW(2,       xz-wy,       yz-wx,  1.0f-xx-yy,  0.0f)
	SET_ROW(3,        0.0f,        0.0f,        0.0f,  1.0f)
}


void Matrixf::makePerspective(float near, float far, float fov, float aspectRatio)
{
	float Y  = 1.0f / tanf(fov * 0.5f);
	float X  = Y * aspectRatio;
	float Z1 = far / (far - near);
	float Z2 = Z1 * (-near);
	
	SET_ROW(0,     X,  0.0f,  0.0f,  0.0f )
	SET_ROW(1,  0.0f,     Y,  0.0f,  0.0f )
	SET_ROW(2,  0.0f,  0.0f,    Z1,    Z2 )
	SET_ROW(3,  0.0f,  0.0f,  1.0f,  0.0f )
}