#pragma once

#include "vectorintrinsics.h"

namespace Sonicteam {
namespace SoX {
namespace Math {

struct Vector2 {
	float x, y;

	Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}
	float Dot(const Vector2 &rhs) const;
	Vector2 operator+(const Vector2 &rhs) const;
	Vector2 operator-(const Vector2 &rhs) const;
	Vector2 operator*(float) const;

	float Length() const;
};

struct Vector3 {
	XMVECTOR xyz;

	Vector3(XMVECTOR _xyz) { xyz = _xyz; }
	Vector3 operator-(const Vector3 &rhs) const;

	float LengthSqr() const;
	float DistSqr(const Vector3 &rhs) const;

	operator XMVECTOR() const { return xyz; }
};

struct Vector {
	XMVECTOR v;

	Vector() {}
	Vector(XMVECTOR xyzw) { v = xyzw; }
	Vector(const Vector3 &xyz, float w);

	Vector operator+(const Vector &rhs) const;
	Vector operator-(const Vector &rhs) const;
	const Vector &operator*=(float f);
	Vector operator*(float f) const;

	Vector Lerp(const Vector &rhs, float pct) const;

	operator XMVECTOR() const { return v; }
};

struct ByteVector {
	u8 a, r, g, b;
	ByteVector(u8 _r, u8 _g, u8 _b);
	ByteVector(u8 _a, u8 _r, u8 _g, u8 _b);
};
} // namespace Math
} // namespace SoX
} // namespace Sonicteam
