#pragma once
#include <string>

class Card
{
public:
	virtual ~Card() = default;

private:
	virtual std::string to_string() const noexcept { return "<base card>"; };
};
