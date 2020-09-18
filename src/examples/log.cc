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
	strftime(time_buf, arraysize(time_buf), "%Y%m%d", &local_time);
#elif defined(OS_POSIX)
	localtime_r(&current_time, &local_time);
	strftime(time_buf, arraysize(time_buf), "%Y%m%d", &local_time);
#endif

	base::FilePath log_path;
	base::FilePath log_filedir;
	base::FilePath log_exename;
	PathService::Get(base::FILE_EXE, &log_exename);
	base::FilePath base_name = log_exename.BaseName().RemoveExtension();
#if defined(OS_WIN)
	PathService::Get(base::DIR_EXE, &log_filedir);
	log_filedir = log_filedir.AppendASCII("log");
	std::string filename = base::StringPrintf("%s%s.log", base::UTF16ToASCII(base_name.value()).c_str(), time_buf);
#elif defined(OS_POSIX)
	log_filedir = base::FilePath::FromUTF8Unsafe(base::StringPrintf("/var/log/%s", base_name.value().c_str()));
	std::string filename = base::StringPrintf("%s%s.log", base_name.value().c_str(), time_buf);
#endif

	if (!base::DirectoryExists(log_filedir)) {
		base::CreateDirectoryAndGetError(log_filedir, NULL);
	}

	log_path = log_filedir.AppendASCII(filename.c_str());
	logging::LoggingSettings settings;
	settings.logging_dest = logging::LOG_TO_ALL;
	settings.log_file = log_path.value().c_str();
	settings.delete_old = logging::APPEND_TO_OLD_LOG_FILE;
	logging::InitLogging(settings);
	//Log saving options: process ID, thread ID, timestamp, tick count
	logging::SetLogItems(true,    // enable_process_id
						 true,    // enable_thread_id
						 true,    // enable_timestamp
						 false);  // enable_tickcount
}

int main(int argc, char** argv) {

	// setp 1
	base::CommandLine::Init(argc, argv);

	// setp 2
	InitLogging();

	//INFO, WARNING, ERROR
	LOG(INFO) << "Info message";
	LOG(WARNING) << "Warning message";
	LOG(ERROR) << "Error message";

	LOG(INFO) << "ÖÐ¹ú£¬ÄãºÃ£¡";

	//DLOG is similar to LOG, the difference is that DLOG only takes effect in DEBUG mode
	DLOG(INFO) << "debug mode message";

	//Use the LOG_IF macro to output log only when the expression condition is true
	int a = 1;
	LOG_IF(INFO, a < 3) << "if a < 3";

	// PLOG macro also appends the last error information of the system.
	// GetLastError() on windows, errno on POSIX
	PLOG(ERROR) << "Open file failed, LastError";

	return 0;
}