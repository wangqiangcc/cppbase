#include <iostream>
#include <string>
#include <windows.h>
#include "base/process/process_metrics.h"
#include "base/process/process.h"
#include "base/process/launch.h"

int main(int argc, char** argv) {
  
	int process_id = 0;
	if (argc >= 2) {
		process_id = std::stoi(std::string(argv[1]));
	}

	size_t page_size = base::GetPageSize();
	std::cout << "page_size: " << page_size << std::endl;

	base::SystemMemoryInfoKB info;
	base::GetSystemMemoryInfo(&info);
	std::cout << "mem total: " << info.total / 1024 << " mem free: " << info.free / 1024 << std::endl;


	base::ProcessMetrics *metrics = NULL;
	if (process_id <= 0) {
		metrics = base::ProcessMetrics::CreateCurrentProcessMetrics();
	}
	else {
		base::ProcessHandle process_handle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
		metrics = base::ProcessMetrics::CreateProcessMetrics(process_handle);
	}

	for (int i = 0; i < 100; i++) {

		size_t private_bytes;
		size_t shared_bytes;
		metrics->GetMemoryBytes(&private_bytes, &shared_bytes);
		std::cout << "private_bytes: " << private_bytes / 1024 / 1024 << " shared_bytes: " << shared_bytes / 1024 / 1024 << " \nworking set size(mem): " << metrics->GetWorkingSetSize()/1024/1000 << std::endl;

		double cpu_usage = metrics->GetCPUUsage();
		std::cout << "cpu_usage: " << cpu_usage << std::endl;
		Sleep(1000);
	}

	// startup process
	base::LaunchOptions options;
	base::Process process = base::LaunchProcess(L"c:\\Windows\\SysWow64\\notepad.exe", options);
	int priority = process.GetPriority();
	process.Close();

  return 0;
}
