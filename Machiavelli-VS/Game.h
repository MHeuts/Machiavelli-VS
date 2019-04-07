#pragma once
#include "StateMachine.h"
#include "deck.h"

class Player;

class Game {
public:
	Game();
	~Game() = default;

private:
	std::vector<std::weak_ptr<ClientInfo>> clients;
	StateMachine stateMachine;
	bool running_{false};
	deck deck_;

	// 0 or 1 for the current player
	int currentKing_;
	int currentPlayer_;

public:
	void HandleClientCommand(const ClientCommand& command);

	static std::shared_ptr<Game> instance();
	void AddClient(std::weak_ptr<ClientInfo> client);

	int getCurrentPlayer() const { return currentPlayer_; }
	int getKing() const { return currentKing_; }

	void setKing(int king) { currentKing_ = king; }
	void setCurrentPlayer(int player) { currentPlayer_ = player; }

	bool isRunning() const { return running_; }
	bool PlayersReady() const { return clients.size() == 2; }
	std::shared_ptr<ClientInfo> getCurrentClient() { return clients[currentPlayer_].lock(); };
	void setup();
};
