#include "pch.h"
#include "Game.h"
#include <utility>
#include "player_card.h"

player_card::player_card(const std::string name) : player_card(name, "grey")
{
}

player_card::player_card(const std::string name, const std::string color) : name(name), color(color)
{
}

bool player_card::operator==(const player_card right) const noexcept
{
	return order == right.order;
}

void player_card::build_building(const std::shared_ptr<building_card>& card) const noexcept
{
	card->is_built = true;
}

int player_card::bonus() const noexcept
{
	if (color == "grey") return 0;

	int bonus = 0;

	for (const auto& card : Game::instance()->current_client->get_player().building_cards)
	{
		if (!card->is_built || card->color != color) continue;

		bonus++;
	}

	return bonus;
}

bool player_card::can_build_buildings(const int number_built) const noexcept
{
	return number_built < 8;
}
