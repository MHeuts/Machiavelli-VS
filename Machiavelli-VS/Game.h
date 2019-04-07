#pragma once
#include "StateMachine.h"
#include "deck.h"

class Player;

class Game {
private:
	std::vector<std::weak_ptr<ClientInfo>> clients;
	StateMachine stateMachine;
	bool running_{false};
	deck deck_;

public:
	Game();
	~Game() = default;
	void HandleClientCommand(const ClientCommand& command);

	static std::shared_ptr<Game> instance();
	void AddClient(std::weak_ptr<ClientInfo> client);

	bool isRunning() const { return running_; }
	bool PlayersReady() const { return clients.size() == 2; }

	void setup();
};
