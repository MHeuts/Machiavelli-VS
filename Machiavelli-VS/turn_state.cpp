#include "pch.h"
#include "turn_state.h"
#include "round_start.h"
#include "game_over_state.h"
#include "check_enemy_state.h"
#include "create_building_state.h"
#include "draw_building_card_state.h"

turn_state::turn_state() : turn_state(nullptr)
{
}

turn_state::turn_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
	determine_next_player();
}

void turn_state::enter_state()
{
	switch_state = false;

	const auto game = Game::instance();

	game->client1->render_screen();
	game->client2->render_screen();
}

void turn_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();

	if (client == Game::instance()->current_client)
	{
		client->get_socket() << round_header(client) << Socket::endl
			<< client->get_player().get_turn().build_view()
			<< Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to play their turn." << Socket::endl;
	}
}

void turn_state::handle_input(std::shared_ptr<ClientCommand>& command)
{
	const auto game = Game::instance();
	const auto client = command->get_client_info().lock();

	if (client != game->current_client) return;

	int action = -1;
	try
	{
		action = atoi(command->get_cmd().c_str());
	}
	catch (...) {}

	auto& turn = client->get_player().get_turn();

	if (action == 1)
	{
		game->go_to_state<check_enemy_state>();
		return;
	}

	if (action == 2)
	{
		if (turn.did_get_commodity())
		{
			client->set_message("You already got your commodity for this turn.");
		}
		else
		{
			client->set_message("You received 2 gold.");
			client->get_player().gold += 2;
			turn.get_commodity();
		}

		return;
	}

	if (action == 3)
	{
		const auto amount_picked = game->current_card->pickable_buildings;

		if (turn.amount_picked() >= amount_picked)
		{
			if (turn.amount_picked() == amount_picked)
			{
				client->set_message("You've already picked your building(s) for this turn.");
			}
			else if (turn.amount_picked() > amount_picked)
			{
				client->set_message("You already got your commodity for this turn.");
			}
		}
		else
		{
			pick_building_card = true;
		}

		return;
	}

	if (action == 4)
	{
		building_building = true;
		return;
	}

	if (action == 5)
	{
		if (turn.did_use_ability())
		{
			client->set_message("You already used your card's ability this turn.");
		}
		else
		{
			game->current_card->ability();
			use_ability = true;
		}

		return;
	}

	if (action == 6)
	{
		determine_next_player();
	}
}

void turn_state::update()
{
	const auto game = Game::instance();

	if (building_building)
	{
		game->go_to_state<create_building_state>();
		building_building = false;
	}

	if (pick_building_card)
	{
		game->go_to_state<draw_building_card_state>();
		pick_building_card = false;
	}

	if (use_ability)
	{
		game->current_card->ability_update();
		use_ability = false;
	}

	if (switch_state)
	{
		if (game->winner != nullptr)
		{
			game->go_to_state<GameOverState>(true);
		}
		else
		{
			game->go_to_state<round_start_state>(true);
		}
	}
}

void turn_state::determine_next_player()
{
	const auto game = Game::instance();

	bool found = false;
	current_order++;

	while (current_order <= 8)
	{
		const auto card = game->character_deck.get_original_cards().at(current_order - 1);

		found = check_player_card(game->client1, card);

		if (found) break;

		found = check_player_card(game->client2, card);

		if (found) break;

		current_order++;
	}

	switch_state = current_order > 8;
}

bool turn_state::check_player_card(const std::shared_ptr<ClientInfo> client, const std::shared_ptr<player_card> card) const
{
	if (!client->get_player().has_card(card)) return false;

	if (card->killed)
	{
		client->set_message("Your " + card->name + " card was killed by the Assassin.");
	}
	else
	{
		switch_card(client, card);
		return true;
	}

	return false;
}

std::string turn_state::round_header(const std::shared_ptr<ClientInfo> client)
{
	const auto player = client->get_player();

	std::stringstream card;

	card << "Current character: " << Game::instance()->current_card->name << Socket::endl << Socket::endl
		<< player.building_cards_view() << Socket::endl << player.cards_view();

	return card.str();
}

void turn_state::switch_card(const std::shared_ptr<ClientInfo>& client, const std::shared_ptr<player_card>& card) const
{
	const auto game = Game::instance();
	const auto opponent = game->current_client;
	game->current_card = card;
	game->set_player(client);

	if (game->current_card->robbed)
	{
		const auto current_player_gold = game->current_client->get_player().gold;
		game->current_client->get_player().gold -= current_player_gold;
		opponent->get_player().gold += current_player_gold;

		opponent->set_message("You robbed your opponent of " + std::to_string(current_player_gold) + " gold.");
		game->current_client->set_message("You got robbed of " + std::to_string(current_player_gold) + " gold.");
	}

	const int bonus = card->bonus();

	if (bonus < 1) return;

	client->get_player().gold += bonus;
	client->set_message("The " + card->name + " got a " + std::to_string(bonus) + " gold bonus.");
}
