#pragma once
#include <string>
#include <vector>

class base_card
{
	virtual ~base_card() = default;
	virtual std::string print() const = 0;
};
