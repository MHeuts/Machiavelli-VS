#pragma once
#include "StateMachine.h"

class Game {
public:
	Game();
	~Game() = default;

private:
	std::vector<std::weak_ptr<ClientInfo>> clients;
	StateMachine stateMachine;
	bool running_{false};

public:
	void HandleClientCommand(const ClientCommand& command);

	static std::shared_ptr<Game> instance();
	void AddClient(std::weak_ptr<ClientInfo> client);

	bool isRunning() const { return running_; }
	bool PlayersReady() const { return clients.size() == 2; }

	void setup();

private:
	void shuffleBuildings();
};
