#pragma once
#include <vector>

class file_reader
{
protected:
	file_reader() = default;

public:
	std::vector<std::vector<std::string>> process_csv(std::ifstream& ifstream) const;
};
