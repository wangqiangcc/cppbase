#include <iostream>
#include "base/files/file_util.h"
#include "base/files/file_path.h"
#include "base/path_service.h"

int main(int argc, char** argv) {

	base::FilePath file_exe;
	base::FilePath file_module;
	base::FilePath dir_temp;
	PathService::Get(base::FILE_EXE, &file_exe);
	std::cout << "FILE_EXE: " << file_exe.value() << std::endl;

	PathService::Get(base::FILE_MODULE, &file_module);
	std::cout << "FILE_MODULE: " << file_module.value() << std::endl;

	PathService::Get(base::DIR_TEMP, &dir_temp);
	std::cout << "DIR_TEMP: " << dir_temp.value() << std::endl;


	for (uint32_t n = base::DIR_CURRENT; n < base::PATH_END; ++n)
	{
		base::FilePath dir_test;
		PathService::Get(n, &dir_test);
		std::cout << "DIR BasePathKey: " << n  << " value: " << dir_test.value() << std::endl;
	}

	return 0;
}