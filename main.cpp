// ExpandTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Expand.h"

struct Files
{
	std::ifstream input;
	std::ofstream output;
};

void AddParamsToBohr(Dictionary params)
{
    Dictionary::iterator it = params.begin();

    for (; it != params.end(); it++)
    {
        AddStringToBohr(it->first);
    }
}

std::optional<Files> OpenFiles(std::string inputFileName, std::string outputFileName)
{
	Files files;
	//Открываем входной файл
	files.input.open(inputFileName);
	if (!files.input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		return std::nullopt;
	}
	//Открываем выходной файл
	files.output.open(outputFileName);
	if (!files.output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		return std::nullopt;
	}
	return files;
}

bool ExpandTemplatesInFile(std::string inputFileName, std::string outputFileName, Dictionary params)
{
	std::cout << "start" << std::endl;
	std::ifstream input;
	std::ofstream output;
	input.open(inputFileName);
	output.open(outputFileName);
	std::string buffer;
	while (getline(input, buffer))
	{
		std::cout << buffer << std::endl;
		output<< ExpandTemplate(buffer, params) << std::endl;
	}

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
    setlocale(0, "");

    auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

    InitBohr();

	AddParamsToBohr(args->params);

	if (!ExpandTemplatesInFile(args->inputFileName, args->outputFileName, args->params))
	{
		return 1;
	}

	return 0;
 /*   std::string const tpl = "abba";
    Dictionary params;
    params["a"] = "ab";
    params["bba"] = "z";
    //params["b"] = "c";
    AddStringToBohr("a"); 
    AddStringToBohr("bba");
    //add_string_to_bohr("b");
    auto result = ExpandTemplate(tpl, params);
    std::cout << result << std::endl;*/
/*  auto result = find_all_pos("abcde");
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << result[i].first << ' ' << result[i].second << std::endl;
    }
    std::string str = "abcde";
    str.erase(1, 2);
    std::cout << str;*/  
}
