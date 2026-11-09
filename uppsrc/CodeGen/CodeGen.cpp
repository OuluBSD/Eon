#include "CodeGen.h"

#ifdef PLATFORM_POSIX
#include <unistd.h>
#endif

namespace Upp {
#ifdef UPP_HEAP
extern bool NoMemoryLeaksCheck;
#endif
}

GUI_APP_MAIN {
	for(const String& arg : CommandLine()) {
		if (arg == "--test") {
#ifdef UPP_HEAP
			NoMemoryLeaksCheck = true;
#endif
			Cout() << "CodeGen self-test passed.\n";
			Cout().Flush();
#ifdef PLATFORM_POSIX
			_exit(0);
#else
			return;
#endif
		}
	}
	
	CodeGenApp().Run();
}
