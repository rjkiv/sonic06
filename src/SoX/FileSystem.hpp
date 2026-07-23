#pragma once
namespace Sonicteam {
namespace SoX {
class FileSystem {
public:
	FileSystem();
	virtual void V_Unk0x0() = 0;
	virtual void V_Unk0x4() = 0;
	virtual void V_Unk0x8() = 0;
	virtual ~FileSystem();
};
} // namespace SoX
} // namespace Sonicteam
