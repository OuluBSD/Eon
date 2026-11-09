#include "Shell.h"

NAMESPACE_UPP

void MachineEcsInit(Engine& mach) {
}

void EngineEcsInit(Engine& eng) {
	eng.GetAdd<InteractionSystem>();
}

END_UPP_NAMESPACE
