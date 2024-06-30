#ifndef MATRIX_H
#define MATRIX_H

#include "Vec.h"


class Matrixf
{
public:
	Matrixf() {}
	
	Matrixf(const Matrixf& other) { set(other); }

	Matrixf(Matrixf&& other) { std::swap(_mat, other._mat); }
	
	Matrixf& operator = (const Matrixf& other) { set(other); return *this; }
	// Matrixf& operator = (Matrixf&& other) { std::swap(_mat, other._mat); }
	
	inline float operator () (int row, int col) const { return _mat[row][col]; }
	inline float& operator () (int row, int col) { return _mat[row][col]; }
	
	Vec4f operator * (const Vec4f& vec) const;
	
	inline Matrixf operator * (const Matrixf& mat) const
	{
		Matrixf res;
		res.mult(*this, mat);
		return res;
	};

	inline void set(const Matrixf& mat)
	{
		for (int i = 0; i < 16; i++) ((float*)_mat)[i] = ((float*)mat._mat)[i];
	}
	
	Vec4f postMult(const Vec4f& vec) const;
	void postMult(const Matrixf& mat);
	void mult(const Matrixf& m1, const Matrixf& m2);
	
	void makeIdentity();
	void makeTranslate(const Vec3f& vec);
	void makeRotate(float angle, const Vec3f& axis);
	void makePerspective(float near, float far, float fov, float aspectRatio);
	
	static inline Matrixf identity()
	{
		Matrixf mat;
		mat.makeIdentity();
		return mat;
	}
	
	static inline Matrixf translate(const Vec3f& vec)
	{
		Matrixf mat;
		mat.makeTranslate(vec);
		return mat;
	}
	
	static inline Matrixf rotate(float angle, const Vec3f& axis)
	{
		Matrixf mat;
		mat.makeRotate(angle, axis);
		return mat;
	}
	
	static inline Matrixf perspective(float near, float far, float fov, float aspectRatio)
	{
		Matrixf mat;
		mat.makePerspective(near, far, fov, aspectRatio);
		return mat;
	}

protected:
	float _mat[4][4];

};


#endif