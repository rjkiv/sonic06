#pragma once

#include "SoX/Math/Vector.hpp"
#include "vectorintrinsics.h"

namespace Sonicteam {
namespace SoX {
namespace Math {

struct Matrix {
	XMVECTOR c0, c1, c2, c3;

	Vector operator*(const Vector &rhs);
	const float &operator()(int col, int row) const;
	float &operator()(int col, int row);
};

} // namespace Math
} // namespace SoX
} // namespace Sonicteam
