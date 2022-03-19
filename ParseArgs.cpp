#include <iostream>
#include <optional>
struct Args
{
	std::string inputFileName;
	std::string outputFileName;

};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: expand_template.exe <input file name> <output file name> [<param> <value> [<param> <value> …]]\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}