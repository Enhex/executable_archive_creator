#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "archive_src.h"
#include "archive_info.h"

int main()
{
	char constexpr dir_path[] = "/tmp/ea/";
	system("mkdir -p /tmp/ea");
	chdir("/tmp/ea");

	//TODO make sure the dir_path/archive_name filepath doesn't exist

	// save archive bytes to file
	char constexpr extract_cmd[] = "tar -xf ";
	// using str for both archive write and extract by passing an offsetted char*
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
	system(str);
	free(str);

	// run command
	system(run_command);
}