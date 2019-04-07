#pragma once

#include <fstream>
#include <vector>

class CsvReader
{
protected:
	CsvReader() = default;

public:
	std::vector<std::vector<std::string>> process_csv(std::ifstream& ifstream) const;
};


