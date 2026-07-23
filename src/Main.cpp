#include "SoX/platforms/Xenon/FileSystemXenon.hpp"

Sonicteam::SoX::FileSystemXenon TheFS;

int main(int argc, char **argv) {
	static Sonicteam::SoX::FileSystemXenon *fs = &TheFS.GetSingleton();
	return 0;
}
