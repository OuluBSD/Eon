#ifndef _Shell_Shell_h_
#define _Shell_Shell_h_

#include <Core/Core.h>
#include <Geometry/Geometry.h>
#include <Vfs/Vfs.h>
#include <Eon/Core/Core.h>
#include <Eon/Ecs/Ecs.h>
#include <Eon/Compiler/Compiler.h>
#include <Eon/Script/Script.h>

NAMESPACE_UPP

void MachineEcsInit(Engine& mach);
void EngineEcsInit(Engine& eng);
void BindEcsToSerial();

END_UPP_NAMESPACE

Upp::Engine& ShellMainEngine();
void ShellMain(bool skip_eon);

#endif


