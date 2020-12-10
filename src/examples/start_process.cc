#include <iostream>
#include <string>
#include "base/process/process_metrics.h"
#include "base/process/process.h"
#include "base/process/launch.h"
#include "base/threading/platform_thread.h"

int main(int argc, char** argv) {
	base::LaunchOptions options;
	base::Process process = base::LaunchProcess(L"c:\\windows\\notepad.exe", options);
	return 0;
}
