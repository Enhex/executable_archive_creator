#include <cstdlib>
#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <iterator>

namespace fs = std::filesystem;

auto file_to_bytes(char* filepath)
{
	std::ifstream file(filepath, std::ios::binary);

	std::string output =
		"#pragma once\n"
		"unsigned char constexpr archive_file_bytes[] = {";
	auto iter = std::istreambuf_iterator<char>(file);
	auto const end = std::istreambuf_iterator<char>();
	if(iter != end)  {
		output += fmt::format("0x{:x}", (unsigned char)*iter);
		++iter;
	}
	for(; iter != end; ++iter) {
		output += fmt::format(",0x{:x}", (unsigned char)*iter);
	}
	output += "};";

	return output;
}

int main(int argc, char* argv[])
{
	if (argc != 4) {
		fmt::print("usage: eac <tar.xz archive file> <output file> <run command>\n");
		return EXIT_FAILURE;
	}

	fmt::print("{}\n", argv[1]);

	//TODO use /tmp
	fs::path const output_dir = fs::current_path() / "output";
	fs::create_directories(output_dir);

	// generate bytes array source file
	{
		auto const archive_src = file_to_bytes(argv[1]);
		std::ofstream ofile(output_dir / "archive_src.h", std::ios::binary);
		ofile << archive_src;
	}

	// archive info
	{
		std::ofstream ofile(output_dir / "archive_info.h", std::ios::binary);
		std::string content =
			"#pragma once\n"
			"char constexpr archive_name[] = \"";
		content += fs::path(argv[1]).filename().string();
		content += "\";\n"
			"auto constexpr run_command = \"";
		content += argv[3];
		content += "\";";
		ofile << content;
	}

	// compile the executable archive
	auto const command = fmt::format("premake5 --verbose --file=./data/premake5.lua --location=\"{}\" --name=\"{}\" gmake2", output_dir.string(), argv[2]);
	std::system(command.c_str());
	// {
	// 	auto const command = fmt::format("premake5 --verbose --file=./data/premake5.lua --location=\"{}\" --name=\"{}\" vscode", output_dir.string(), argv[2]);
	// 	std::system(command.c_str());
	// }
	std::system("make -r -C ./output config=release");
}
