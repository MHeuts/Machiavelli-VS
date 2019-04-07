#include "pch.h"
#include <iostream>
#include "building_deck.h"


void building_deck::reset()
{
	cards.clear();

	for (const auto& card : original_cards)
	{
		if (card->is_built) continue;

		cards.push_back(card);
	}
}

std::ifstream& operator>>(std::ifstream& ifstream, building_deck& deck)
{
	try
	{
		const auto matrix = deck.process_csv(ifstream);

		for (const auto& vector : matrix)
		{
			// Skip purple cards
			if (vector.at(2) == "purple") continue;

			const auto card = std::make_shared<building_card>(
				vector.at(0), atoi(vector.at(1).c_str()), vector.at(2), vector.at(3)
				);

			deck.original_cards.push_back(card);
		}
	}
	catch (...)
	{
		std::cerr << "Invalid building file" << std::endl;
	}

	deck.reset();

	return ifstream;
}

std::ostream& operator<<(std::ostream& ostream, const building_deck& deck)
{
	for (const auto& card : deck.cards)
	{
		ostream << "(" << card->price << ") " << card->color << "; " << card->name;

		if (!card->ability.empty())
		{
			ostream << ", " << card->ability;
		}

		ostream << std::endl;
	}

	return ostream;
}
