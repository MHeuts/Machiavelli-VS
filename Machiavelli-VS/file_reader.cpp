#include "pch.h"
#include "file_reader.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include "color_enum.h"

building_card filereader::create_building_card(std::vector<std::string> attributes) const
{
	color color{};
	if (attributes[2] == "geel") color = YELLOW;
	if (attributes[2] == "groen") color = GREEN;
	if (attributes[2] == "blauw") color = BLUE;
	if (attributes[2] == "rood") color = RED;

	building_card card{ attributes[0], std::stoi(attributes[1]) , color };
	return card;
}

player_card filereader::create_player_card(const std::string& attributes) const
{
	player_card card{ std::stoi(attributes.substr(0, attributes.find(';'))), attributes.substr(2, attributes.length() -1) };
	return card;
}

std::vector<player_card> filereader::read_player_cards() const
{
	std::vector<player_card> cards;
	std::ifstream fileStream;
	fileStream.open("Assets/karakterkaarten.csv");
	std::string str;
	std::vector<std::string> card;

	int count = 0;
	while (std::getline(fileStream, str))
	{
		cards.push_back(create_player_card(str));
		count = 0;
		card.clear();
	}
	return cards;
}

std::vector<building_card> filereader::read_building_cards() const
{
	std::vector<building_card> cards;
	std::ifstream fileStream;
	fileStream.open("Assets/Bouwkaarten.csv");
	std::string str;
	std::vector<std::string> card;

	int count = 0;
	while (std::getline(fileStream, str, ';'))
	{
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		card.push_back(str);
		count++;
		if(count == 3)
		{
			cards.push_back(create_building_card(card));
			count = 0;
			card.clear();
		}
	}
	return cards;
}
