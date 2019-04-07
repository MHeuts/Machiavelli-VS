#include "GameOverState.h"
#include "Game.h"

void GameOverState::enter_state()
{
	auto const game = Game::instance();
	showScoreScreen(game->client1);
	showScoreScreen(game->client2);
}

void GameOverState::showScoreScreen(const std::shared_ptr<ClientInfo> client)
{
	auto const game = Game::instance();
	const auto opponent = client == game->client1 ? game->client2 : game->client1;

	const int buildingScore = calculateBuildingScore(client);
	const int o_buildingScore = calculateBuildingScore(opponent);

	client->get_socket << "For all your buildings you scored " << buildingScore << "Points!\r\n";
	client->get_socket << "Your opponent scored " << o_buildingScore << " building Points\r\n";

	int cityScore = calculateCityScore(client);
	int o_cityScore = calculateCityScore(opponent);

	if(cityScore == 4)
		client->get_socket << "You Finished Your City First you get 4 Points!\r\n";
	else if(cityScore == 2)
		client->get_socket << "You Finished Your City you get 2 Points!\r\n";

	if(o_cityScore == 4)
		client->get_socket << "Your Opponent Finished His City First het gets 4 Points!\r\n";
	else if (o_cityScore == 2)
		client->get_socket << "Your Opponent Finished His City het gets 2 Points!\r\n";

	int colorScore = calculateColorScore(client);
	int o_colorScore = calculateColorScore(opponent);

	if(colorScore == 3)
		client->get_socket << "You have all colours in your City, you get 3 Points!\r\n";

	if (o_colorScore == 3)
		client->get_socket << "Your opponent has all colours in his City, he gets 3 Points!\r\n";

	int totalScore = colorScore + cityScore + buildingScore;
	int o_totalScore = o_colorScore + o_cityScore + o_buildingScore;

	client->get_socket << "Your finished the game with "<< totalScore << " Points!\r\n";
	client->get_socket << "Your opponent finished the game with "<< totalScore << " Points!\r\n";

	if (totalScore > o_totalScore)
	{
		client->get_socket << "Congratulations You won!" << Socket::endl;
	}
	else if (totalScore < o_totalScore)
	{
		client->get_socket << "You Lost!" << Socket::endl;
	}
	else
	{
		client->get_socket << "It's a tie!" << Socket::endl;

		if (buildingScore > o_buildingScore)
		{
			client->get_socket << "You won because you have more building points." << Socket::endl;
		}
		else if (buildingScore < o_buildingScore)
		{
			client->get_socket << "You lost because you have less building points." << Socket::endl;
		}
	}
}

int GameOverState::calculateBuildingScore(const std::shared_ptr<ClientInfo> client)
{
	int score {0};
	for (auto building = client->get_player().building_cards.begin(); building!= client->get_player().building_cards.end(); ++building)
	{
		if ((*building)->is_built) continue;

		score += (*building)->price;
	}

	return score;
}

int GameOverState::calculateCityScore(const std::shared_ptr<ClientInfo> client)
{
	if (Game::instance()->winner == client)
		return 4;
	if (client->get_player().number_built_buildings() >= 8)
		return 2;
	return 0;
}

int GameOverState::calculateColorScore(const std::shared_ptr<ClientInfo> client)
{
	bool red{ false }, blue{ false }, yellow{ false }, green{ false }, purple {false};

	for (auto building = client->get_player().building_cards.begin(); building != client->get_player().building_cards.end(); ++building)
	{
		if (!(*building)->is_built)
			continue;
		if ((*building)->color == "red")
			red = true;
		else if ((*building)->color == "blue")
			blue = true;
		else if ((*building)->color == "yellow")
			yellow = true;
		else if ((*building)->color == "green")
			green = true;
		else if ((*building)->color == "purple")
			purple = true;
	}
	if (red && blue && yellow && green && purple)
		return 3;
	return 0;
}
