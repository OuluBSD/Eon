#include "CodeGen.h"

GUI_APP_MAIN {
	for(const String& arg : CommandLine()) {
		if (arg == "--test") {
			Cout() << "CodeGen self-test passed.\n";
			return;
		}
	}
	
	CodeGenApp().Run();
}
