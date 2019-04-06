#pragma once
#include "StateMachine.h"

class Game {
private:
	std::vector<std::weak_ptr<ClientInfo>> clients;

	StateMachine stateMachine;
public:
	Game();
	~Game() = default;
	void HandleClientCommand(const ClientCommand& command);

	static std::shared_ptr<Game> instance();

	void AddClient(std::weak_ptr<ClientInfo> client);

	bool isRunning() const;
	bool PlayersReady() const { return clients.size() == 2; }
	void setup();


};
