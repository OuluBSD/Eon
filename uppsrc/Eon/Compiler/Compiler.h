#ifndef _Eon_Compiler_Compiler_h_
#define _Eon_Compiler_Compiler_h_

#include <Core/Core.h>
#include <Vfs/Core/Core.h>
#include <Esc/Esc.h>

NAMESPACE_UPP

#include "Defs.h"
#include "Node.h"
#include "Util.h"
#include "Ast.h"
#include "EonStd.h"
#include "Exporter.h"
#include "TokenStructure.h"
#include "SemanticParser.h"
#include "AstRunner.h"
#include "AstExporter.h"
#include "CompilerClass.h"

void InitEonCompiler();

END_UPP_NAMESPACE

#endif
