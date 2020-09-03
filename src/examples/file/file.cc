#include <iostream>
#include "base/files/file_util.h"
#include "base/files/file_path.h"
#include "base/files/file.h"
#include "base/files/scoped_temp_dir.h"

int main(int argc, char** argv) {

	// Temp file 
	base::ScopedTempDir temp_dir;
	temp_dir.CreateUniqueTempDir();
	base::FilePath file_path = temp_dir.path().AppendASCII("create_file_1");

	// Create a file.
	base::File file(file_path,
		base::File::FLAG_OPEN_ALWAYS | base::File::FLAG_READ |
		base::File::FLAG_SHARE_DELETE);

	bool bValid = file.IsValid();
	bool bCreated = file.created();

	if (base::File::FILE_OK != file.error_details()) {
		std::cout << "error_details: " << file.error_details() << std::endl;
	}

	// Open an existing file and mark it as delete on close.
	base::File same_file(file_path,
		base::File::FLAG_OPEN | base::File::FLAG_DELETE_ON_CLOSE |
		base::File::FLAG_READ | base::File::FLAG_WRITE);


	char data_to_write[] = "test";
	// Write to the file.
	int bytes_written = same_file.Write(0, data_to_write, strlen(data_to_write));

	// Get file size
	int64_t file_size = 0;
	GetFileSize(file_path, &file_size);

	// Read from EOF.
	char data_read_1[32];
	int bytes_read = same_file.Read(0, data_read_1, static_cast<int>(file_size));
	data_read_1[file_size] = '\0';

	// Close both handles and check that the file is gone.
	file.Close();
	same_file.Close();
	if (base::PathExists(file_path)) {
		std::cout << "PathExists: " << file_path.value() << std::endl;
	}

	return 0;
}