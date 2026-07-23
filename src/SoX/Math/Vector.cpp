#include "Vector.hpp"
#include "SoX/Math/Matrix.hpp"
#include "vectorintrinsics.h"
#include <math.h>

namespace Sonicteam {
namespace SoX {
namespace Math {

float fn_825D2200(const Vector &v) {
	XMVECTOR ones = __vspltisw(1), zeroes = __vspltisw(0);
	XMVECTOR length_sqr = __vmsum3fp(v, v);
	XMVECTOR halves = __vcfsx(ones, 1);
	XMVECTOR len_est = __vrsqrtefp(length_sqr);
	XMVECTOR half_len_sqr = length_sqr * halves;
	XMVECTOR equality_mask = __vcmpeqfp(length_sqr, zeroes);
	XMVECTOR v9 = len_est * len_est;
	v9 = __vnmsubfp(half_len_sqr, v9, halves);
	v9 = __vmaddfp(len_est, v9, len_est);
	v9 = length_sqr * v9;
	return __vsel(v9, length_sqr, equality_mask).x;
}

float Vector3::LengthSqr() const { return __vmsum3fp(*this, *this).x; }

Vector fn_825D2260(const Vector &v) {
	XMVECTOR ones = __vspltisw(1), zeroes = __vspltisw(0);
	XMVECTOR length_sqr = __vmsum3fp(v, v);
	XMVECTOR halves = __vcfsx(ones, 1);
	XMVECTOR len_est = __vrsqrtefp(length_sqr);
	XMVECTOR half_len_sqr = length_sqr * halves;
	XMVECTOR equality_mask = __vcmpeqfp(length_sqr, zeroes);
	XMVECTOR v9 = len_est * len_est;
	v9 = __vnmsubfp(half_len_sqr, v9, halves);
	v9 = __vmaddfp(len_est, v9, len_est);
	v9 = v * v9;
	return __vsel(v9, length_sqr, equality_mask);
}

Vector::Vector(const Vector3 &xyz, float w) {
	v.x = xyz.xyz.x;
	v.y = xyz.xyz.y;
	v.z = xyz.xyz.z;
	v.w = w;
}

const Vector &Vector::operator*=(float f) {
	XMVECTOR splat;
	splat.v[0] = f;
	splat = __lvlx(&splat.v[0], 0);
	splat = __vspltw(splat, 0);
	v = __vmulfp(*this, splat);
	return *this;
}

Vector Vector::operator*(float f) const {
	XMVECTOR v;
	v.v[0] = f;
	v = __lvlx(&v.v[0], 0);
	v = __vspltw(v, 0);
	return __vmulfp(*this, v);
}

// i thiiink this is translate
Matrix fn_825D2CB0(const Vector &vec) {
	// sneaky trick to generate a vec4 of (0,0,0,1):
	// type 1 is one of the non-4 ones, so it pads like clipspace (i.e. 1 in w)
	Vector zero = __vspltisw(0);
	Vector v0 = __vupkd3d(zero, 1);
	Matrix m;
	m.c0 = __vpermwi(v0, 0xEA);		 // 0b11_10_10_10, WZZZ
	m.c1 = __vpermwi(v0, 0xBA);		 // 0b10_11_10_10, ZWZZ
	m.c2 = __vpermwi(v0, 0xAE);		 // 0b10_10_11_10, ZZWZ
	m.c3 = __vrlimi(v0, vec, 14, 0); // 0b1110
	return m;
}

ByteVector::ByteVector(u8 _r, u8 _g, u8 _b) {
	r = _r;
	g = _g;
	b = _b;
	a = 255;
}

ByteVector::ByteVector(u8 _a, u8 _r, u8 _g, u8 _b) {
	a = _a;
	r = _r;
	g = _g;
	b = _b;
}

Vector Vector::operator+(const Vector &rhs) const {
	return Vector(__vaddfp(v, rhs));
}
Vector3 Vector3::operator-(const Vector3 &rhs) const {
	return Vector3(__vsubfp(*this, rhs));
}

Vector Matrix::operator*(const Vector &rhs) {
	// this is dumb as fuck but the asm requires
	float m30 = (*this)(3, 0);
	float m31 = (*this)(3, 1);
	float m32 = (*this)(3, 2);
	float m33 = (*this)(3, 3);
	float m20 = (*this)(2, 0);
	float m21 = (*this)(2, 1);
	float m22 = (*this)(2, 2);
	float m23 = (*this)(2, 3);
	float m10 = (*this)(1, 0);
	float m11 = (*this)(1, 1);
	float m12 = (*this)(1, 2);
	float m13 = (*this)(1, 3);
	float m00 = (*this)(0, 0);
	float m01 = (*this)(0, 1);
	float m02 = (*this)(0, 2);
	float m03 = (*this)(0, 3);
	Vector out;
	out.v.x = rhs.v.x * m00 + rhs.v.y * m01 + rhs.v.z * m02 + rhs.v.w * m03;
	out.v.y = rhs.v.x * m10 + rhs.v.y * m11 + rhs.v.z * m12 + rhs.v.w * m13;
	out.v.z = rhs.v.x * m20 + rhs.v.y * m21 + rhs.v.z * m22 + rhs.v.w * m23;
	out.v.w = rhs.v.x * m30 + rhs.v.y * m31 + rhs.v.z * m32 + rhs.v.w * m33;
	return out;
}

Vector fn_825D3DB0(const Vector &lhs, const Vector &rhs, float f) {
	Vector v;
	v.v.x = v.v.y = v.v.z = v.v.w = f;
	// v = __vrlimi128(v.v, v.v, 3, 2);
	return __vmaddfp(rhs, v.v, lhs);
}

Vector Vector::Lerp(const Vector &rhs, float f) const {
	XMVECTOR v;
	v.v[0] = f;
	v = __lvlx(&v.v[0], 0);
	v = __vspltw(v, 0);
	return __vmaddfp(rhs - *this, v, *this);
}

float Vector3::DistSqr(const Vector3 &rhs) const {
	return (*this - rhs).LengthSqr();
}

float Vector2::Dot(const Vector2 &rhs) const { return x * rhs.x + y * rhs.y; }

Vector2 Vector2::operator+(const Vector2 &rhs) const {
	return Vector2(x + rhs.x, y + rhs.y);
}
Vector2 Vector2::operator-(const Vector2 &rhs) const {
	return Vector2(x - rhs.x, y - rhs.y);
}
Vector2 Vector2::operator*(float f) const { return Vector2(x * f, y * f); }

float Vector2::Length() const { return sqrtf(Dot(*this)); }

Matrix fn_825D4440() {
	Vector zero = __vspltisw(0);
	Vector v0 = __vupkd3d(zero, 1);
	Matrix m;
	m.c0 = __vpermwi(v0, 0xEA); // 0b11_10_10_10, WZZZ
	m.c1 = __vpermwi(v0, 0xBA); // 0b10_11_10_10, ZWZZ
	m.c2 = __vpermwi(v0, 0xAE); // 0b10_10_11_10, ZZWZ
	m.c3 = __vpermwi(v0, 0xAB); // 0b10_10_10_11, ZZZW
	return m;
}

} // namespace Math
} // namespace SoX
} // namespace Sonicteam
