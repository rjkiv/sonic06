#pragma once

#include "SoX/FileSystem.hpp"
#include "System/Singleton.hpp"

namespace Sonicteam {
namespace SoX {
class FileSystemXenon : public FileSystem,
						public System::Singleton<FileSystemXenon> {
public:
	FileSystemXenon();
	virtual void V_Unk0x0() override;
	virtual void V_Unk0x4() override;
	virtual void V_Unk0x8() override;
	virtual ~FileSystemXenon();
};
} // namespace SoX
} // namespace Sonicteam
