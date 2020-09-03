#include <iostream>
#include <string>
#include <windows.h>
#include "base/command_line.h"

int main(int argc, char** argv) {

	// cmdline.exe --help=hello
	DCHECK(!base::CommandLine::InitializedForCurrentProcess());
	base::CommandLine::Init(argc, argv);

	DCHECK(base::CommandLine::ForCurrentProcess());
	base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
	base::CommandLine::StringType args = command_line->GetCommandLineString();

	std::cout << "args: " << args.c_str() << std::endl;

	if (!command_line->HasSwitch("--help")) {
		std::string help_args = command_line->GetSwitchValueASCII("help");
		std::cout << "--help=" << help_args.c_str() << std::endl;
	}

	return 0;
}
