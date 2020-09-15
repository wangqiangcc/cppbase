#include <iostream>
#include "base/command_line.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/strings/stringprintf.h"
#include "base/strings/sys_string_conversions.h"
#include "base/strings/utf_string_conversions.h"

//init log
void InitLogging() {

	time_t current_time = 0;
	time(&current_time);
	const int BUFFER_SIZE = 64;
	struct tm local_time = { 0 };
	char time_buf[BUFFER_SIZE] = { 0 };
#if defined(OS_WIN)
	localtime_s(&local_time, &current_time);
	//asctime_s(time_buf, arraysize(time_buf), &local_time);
	strftime(time_buf, arraysize(time_buf), "%Y%m%d%H%M%S", &local_time);
#elif defined(OS_POSIX)
	localtime_r(&current_time, &local_time);
	//asctime_r(&local_time, time_buf);
	strftime(time_buf, arraysize(time_buf), "%Y%m%d%H%M%S", &local_time);
#endif

	base::FilePath log_filename;
	base::FilePath log_exename;
	PathService::Get(base::DIR_EXE, &log_filename);
	PathService::Get(base::FILE_EXE, &log_exename);
	base::FilePath base_name = log_exename.BaseName().RemoveExtension();
#if defined(OS_WIN)
	std::string filename = base::StringPrintf("%s%s.log", base::UTF16ToASCII(base_name.value()).c_str(), time_buf);
#elif defined(OS_POSIX)

	std::string filename = base::StringPrintf("%s%s.log", base::SysWideToNativeMB(base::SysUTF8ToWide(base_name.value())).c_str(), time_buf);
#endif
	log_filename = log_filename.AppendASCII("log");

	if (!base::DirectoryExists(log_filename)) {
		base::CreateDirectoryAndGetError(log_filename, NULL);
	}

	log_filename = log_filename.AppendASCII(filename.c_str());
	logging::LoggingSettings settings;
	settings.logging_dest = logging::LOG_TO_ALL;
	settings.log_file = log_filename.value().c_str();
	settings.delete_old = logging::APPEND_TO_OLD_LOG_FILE;
	logging::InitLogging(settings);
	logging::SetLogItems(true, true, true, true);
}

int main(int argc, char** argv) {

	// setp 1
	base::CommandLine::Init(argc, argv);

	// setp 2
	InitLogging();

	//INFO, WARNING, ERROR

	LOG(INFO) << "info text \n\r";
	LOG(WARNING) << "warning text \n\r";
	LOG(ERROR) << "error text \n\r";

	return 0;
}