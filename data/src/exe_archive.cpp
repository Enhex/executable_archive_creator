#include <cstdio>
#include <cstdlib>
#include <string.h>

#include "archive_src.h"
#include "archive_info.h"

int main()
{
	char constexpr dir_path[] = "/tmp/ea/";
	std::system("mkdir -p /tmp/ea");

	//TODO make sure the dir_path/archive_name filepath doesn't exist

	// save archive bytes to file
	char constexpr extract_cmd[] = "tar -xf ";
	auto str = (char*)malloc(sizeof(extract_cmd) + sizeof(dir_path) + sizeof(archive_name) - 2);
	strcpy(str, extract_cmd);
   	strcat(str, dir_path);
   	strcat(str, archive_name);
	{
		auto file = fopen(str+sizeof(extract_cmd)-1, "w");
		if(file == nullptr)
			return EXIT_FAILURE;
		for(auto c : archive_file_bytes)
			fputc(c, file);
		fclose(file);
	}

	// extract archive
	std::system(str);
	free(str);

	// run command
	std::system(run_command);
}