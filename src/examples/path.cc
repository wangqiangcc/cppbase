#include <iostream>
#include "base/files/file_util.h"
#include "base/files/file_path.h"
#include "base/path_service.h"

int main(int argc, char** argv) {

	// File path operation
#ifdef WIN32
	base::FilePath path(L"C:\\Windows");
#else
	base::FilePath path("/home/");
#endif // WIN32

	std::cout << "path: " << path.value() << std::endl;
	base::FilePath path2 = path.AppendASCII("SysWOW64\\log");
	std::cout << "path2: " << path2.value() << std::endl;
	base::FilePath path3 = path2.AppendASCII("test");
	std::cout << "path3: " << path3.value() << std::endl;

#ifdef WIN32
	base::FilePath path4 = path3.AddExtension(L"log");
#else
	base::FilePath path4 = path3.AddExtension("log");
#endif // WIN32
	std::cout << "path4: " << path4.value() << std::endl;

#ifdef WIN32
	base::FilePath path5 = path3.ReplaceExtension(L"txt");
#else
	base::FilePath path5 = path3.ReplaceExtension("txt");
#endif // WIN32
	std::cout << "path5: " << path5.value() << std::endl;

	std::cout << "BaseName: " << path5.BaseName().value() << std::endl;
	std::cout << "DirName: " << path5.DirName().value() << std::endl;
	std::cout << "Extension: " << path5.Extension() << std::endl;



	// Get path
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