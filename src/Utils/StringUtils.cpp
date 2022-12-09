#include "StringUtils.h"

#include <string>
#include <fstream>
#include <sstream>



int endsWith(const char* s, const char* part)
{
	return (strstr(s, part) - s) == (strlen(s) - strlen(part));
}

const std::string ReadShaderFile(const std::string fileName)
{
	std::ifstream file_stream(fileName);

	if (file_stream.fail())
	{
		fprintf(stderr, "Error: %s\n", "Failed to open the file");
		return std::string();
	}

	std::ostringstream str_stream{};
	file_stream >> str_stream.rdbuf();

	if (file_stream.fail() && !file_stream.eof())
	{
		fprintf(stderr, "Error: %s\n", "Error reading file");
		return std::string();
	}

	return str_stream.str();
}

void PrintShaderSource(const std::string& s)
{

}