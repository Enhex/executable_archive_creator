#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string.h>

#include "archive_src.h"
#include "archive_info.h"

int main()
{
	char constexpr dir_path[] = "/tmp/ea/";
	std::system("mkdir -p /tmp/ea");

	//TODO make sure the filepath doesn't exist
	//fs::path const archive_filepath = dir_path + archive_name;

	// save archive bytes to file
	char constexpr extract_cmd[] = "tar -xf ";
	auto str = (char*)malloc(sizeof(extract_cmd) + sizeof(dir_path) + sizeof(archive_name) - 2);
	strcpy(str, extract_cmd);
   	strcat(str, dir_path);
   	strcat(str, archive_name);
	{
		std::ofstream file(str+sizeof(extract_cmd), std::ios::binary);
		file.write((const char*)archive_file_bytes, sizeof(archive_file_bytes));
	}

	// extract archive
	std::system(str);
	free(str);

	// run command
	std::system(run_command);
}