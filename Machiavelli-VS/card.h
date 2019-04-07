#pragma once
#include <string>

class card
{
public:
	virtual ~card() = default;

private:
	virtual std::string to_string() const noexcept { return "<base card>"; };
};
