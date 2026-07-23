#include "ShaderCommon.hpp"
#include "SoX/RefCountObject.hpp"
#include "macros.h"

namespace Sonicteam {
namespace SoX {
namespace Graphics {

ShaderCommon::ShaderCommon() {
	mShaderValues[0] = null;
	mShaderValues[1] = null;
	mShaderValues[2] = null;
	mShaderValues[3] = null;
	mShaderValues[4] = null;
	mShaderValues[5] = null;
	mShaderValues[6] = null;
	mShaderValues[7] = null;
}

ShaderCommon::~ShaderCommon() {
	for (int i = 7; i >= 0; i--) {
		mShaderValues[i]->Release();
	}
}

// this is probably some virtual inheritance bs
void ShaderCommon::SetShaderValue(int index, RefCountObject **new_value_ptr) {
	RefCountObject *new_value = *new_value_ptr;
	if (new_value != null) {
		new_value->Retain();
	}
	RefCountObject *old_value = mShaderValues[index];
	mShaderValues[index] = new_value;
	if (old_value != null) {
		old_value->Release();
	}
}

} // namespace Graphics
} // namespace SoX
} // namespace Sonicteam
