#pragma once

#include "SoX/RefCountObject.hpp"
namespace Sonicteam {
namespace SoX {
namespace Graphics {

class ShaderCommon : public RefCountObject {
public:
	ShaderCommon();
	virtual ~ShaderCommon();
	virtual void SetShaderValue(int index, RefCountObject **new_value);
	virtual void V_Unk8() = 0;
	virtual void V_UnkC() = 0;
	virtual void V_Unk10() = 0;
	virtual void V_Unk14() = 0;
	virtual void V_Unk18() = 0;
	virtual void V_Unk1C() = 0;
	virtual void V_Unk20() = 0;
	virtual void V_Unk24() = 0;
	virtual void V_Unk28() = 0;

private:
	RefCountObject *mShaderValues[8]; // 0x8
};

} // namespace Graphics
} // namespace SoX
} // namespace Sonicteam
