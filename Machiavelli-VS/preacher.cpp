#include "pch.h"
#include "preacher.h"
#include "Game.h"

preacher::preacher() : player_card("Preacher", "blue")
{
}

void preacher::ability() const noexcept
{
	Game::instance()->current_client->set_message(
		"Info: The preacher will help you protect your buildings."
	);
}

void preacher::build_building(const std::shared_ptr<building_card>& card) const noexcept
{
	player_card::build_building(card);
	card->protected_card = true;
}
