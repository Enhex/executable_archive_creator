#include <cstdlib>
#include <filesystem>
#include <fstream>

#include "archive_src.h"
#include "archive_info.h"

namespace fs = std::filesystem;

int main()
{
	fs::path const dir_path = "/tmp/ea";
	fs::create_directories(dir_path);

	//TODO make sure the filepath doesn't exist
	fs::path const archive_filepath = dir_path / archive_name;

	// save archive bytes to file
	{
		std::ofstream file(archive_filepath, std::ios::binary);
		file.write((const char*)archive_file_bytes, sizeof(archive_file_bytes));
	}

	// extract archive
	std::system(("tar -xf " + archive_filepath.string()).c_str());

	// run command
	std::system(run_command);
}