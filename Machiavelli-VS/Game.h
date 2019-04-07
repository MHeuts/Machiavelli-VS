#pragma once
#include "StateMachine.h"
#include "deck.h"


class Game {
public:
	Game();
	~Game() = default;

private:
	std::vector<std::shared_ptr<ClientInfo>> clients_;
	StateMachine stateMachine;
	bool running_{false};
	deck deck_;

	// 0 or 1 for the current player
	int currentKing_;
	size_t currentPlayer_ = 0llu;

public:
	void HandleClientCommand(const ClientCommand& command);

	static std::shared_ptr<Game> instance();
	void AddClient(std::shared_ptr<ClientInfo> client);

	deck getDeck() { return deck_; }

	size_t getCurrentPlayer() const { return currentPlayer_; }
	int getKing() const { return currentKing_; }

	void setKing(int king) { currentKing_ = king; }
	void setCurrentPlayer(int player) { currentPlayer_ = player; }

	bool isRunning() const { return running_; }
	bool PlayersReady() const { return clients_.size() == 2; }
	std::shared_ptr<ClientInfo> getCurrentClient() { return clients_[currentPlayer_]; };
	void setup();
};
