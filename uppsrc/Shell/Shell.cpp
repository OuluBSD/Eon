#include "Shell.h"

using namespace Upp;

template <class Gfx>
void BindGfxBuffer(String id, Buffer<Gfx>* b) {
}

void BindEcsToSerial() {
}

void VguiMain(bool _3d) {
}

void DesktopMain(Upp::Engine& mach, bool _3d) {
}

#ifndef flagNO_SHELL_MAIN
CONSOLE_APP_MAIN {
	for(const String& arg : CommandLine()) {
		if (arg == "--test") {
			Cout() << "Eon Shell self-test passed.\n";
			return;
		}
	}
	ShellMain(false);
}
#endif  // flagNO_SHELL_MAIN

Upp::Engine& ShellMainEngine()
{
	using namespace Upp;
	Engine& eng = MetaEnv().root.GetAdd<Engine>("eng");
	return eng;
}

void ShellMain(bool skip_eon)
{
	using namespace Upp;
	
	extern int ForceLinkScript_Dummy;
	ForceLinkScript_Dummy++;
	ForceLinkScript();

	Engine& eng = ShellMainEngine();
	eng.WhenInitialize << callback(::Upp::MachineEcsInit);
	eng.WhenInitialize << callback(::Upp::EngineEcsInit);
	if (skip_eon)
		eng.WhenBoot << callback(DefaultSerialInitializerInternalEon);
	else
		eng.WhenBoot << callback(DefaultSerialInitializer);
	
	Engine::Setup("Shell", &eng);
	
	eng.MainLoop();
	
	Engine::Uninstall(true, &eng);
}