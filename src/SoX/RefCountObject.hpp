#pragma once

#include "types.h"

namespace Sonicteam {
namespace SoX {

class RefCountObject {
public:
	RefCountObject() : mRefCount(0) {}
	virtual ~RefCountObject() {}

	// names taken from objective-c because i'm lazy
	void Retain() { mRefCount++; }

	void Release() {
		if (--mRefCount == 0) {
			delete this;
		}
	}

private:
	u32 mRefCount;
};
} // namespace SoX
} // namespace Sonicteam
