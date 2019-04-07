//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Revised by Jeroen de Haas on 22/11/2016
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "pch.h"
#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <chrono>
#include "Game.h"
using namespace std;

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "player.h"
#include "ClientInfo.h"

namespace machiavelli {
	const int tcp_port{ 1080 };
	const string prompt{ "machiavelli> " };
}

static bool running = true;

static Sync_queue<ClientCommand> queue;

void consume_command() // runs in its own thread
{
	try {
		while (running) {
			ClientCommand command{ queue.get() }; // will block here unless there are still command objects in the queue
			if (auto clientInfo = command.get_client_info().lock()) {
				auto &client = clientInfo->get_socket();
				auto &player = clientInfo->get_player();
				try {
					auto cmd = std::make_shared<ClientCommand>(command);
					Game::instance()->handle_input(cmd);
					Game::instance()->render(clientInfo);
					// TODO handle command here
					//client << player.name << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
				}
				catch (const exception& ex) {
					cerr << "*** exception in consumer thread for player " << player.name << ": " << ex.what() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
				catch (...) {
					cerr << "*** exception in consumer thread for player " << player.name << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
			}
		}
	}
	catch (...) {
		cerr << "consume_command crashed\n";
	}
}

std::shared_ptr<ClientInfo> init_client_session(Socket client) {

	if (Game::instance()->is_running())
	{
		client << "The game is full!" << Socket::endl;
		return nullptr;
	}

	client << "What's your name?" << Socket::endl;

	std::string name;
	bool done = false;

	while (!done)
	{
		done = client.readline([&name](std::string input) { name = input; });
	}

	client << "How old are you?" << Socket::endl ;

	int age = 0;
	done = false;

	while (!done || age <= 0)
	{
		done = client.readline([&age, &client](std::string input) {
			try
			{
				age = std::stoi(input);
			}
			catch (...)
			{
				std::cout << "Player provided wrong age input" << std::endl;
				
			};
		});
	}

	return std::make_shared<ClientInfo>(std::move(client), Player(name, age));
}

void handle_client(Socket client) // this function runs in a separate thread
{
	try {
		auto client_info = init_client_session(move(client));

		const auto game = Game::instance();
		game->add_client(client_info);

		auto &socket = client_info->get_socket();
		auto &player = client_info->get_player();


		socket << "Welcome, " << player.name << ", have fun playing our game!\r\n" << machiavelli::prompt;

		while (running) { // game loop
			try {
				// read first line of request
				std::string cmd;
				if (socket.readline([&cmd](std::string input) { cmd = input; })) {
					cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.name << "] " << cmd << "\r\n";

					if (cmd == "quit") {
						socket.write("Bye!\r\n");
						break; // out of game loop, will end this thread and close connection
					}
					else if (cmd == "quit_server") {
						running = false;
					}

					ClientCommand command{ cmd, client_info };
					queue.put(command);
				};

			}
			catch (const exception& ex) {
				socket << "ERROR: " << ex.what() << "\r\n";
			}
			catch (...) {
				socket.write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
			}
		}
		game->remove_client(client_info);
	}
	catch (std::exception &ex) {
		cerr << "handle_client " << ex.what() << "\n";
	}
	catch (...) {
		cerr << "handle_client crashed\n";
	}
}

void update_states()
{
	while (running)
	{
		try
		{
			Game::instance()->update();
		}
		catch (const std::runtime_error& ex)
		{
			std::cerr << "Update thread failed" << std::endl << ex.what() << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
int main(int argc, const char * argv[])
{
	// start command consumer thread
	vector<thread> all_threads;
	all_threads.emplace_back(consume_command);
	// create a server socket
	ServerSocket server{ machiavelli::tcp_port };
	all_threads.emplace_back(update_states);
	try {
		cerr << "server listening" << '\n';

		//test deck
		//deck deck;
		//deck.get_card();
		while (running) {
			// wait for connection from client; will create new socket
			server.accept([&all_threads](Socket client) {
				std::cerr << "Connection accepted from " << client.get_dotted_ip() << "\n";
				all_threads.emplace_back(handle_client, move(client));
			});
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}
	catch (const exception& ex) {
		cerr << ex.what() << ", resuming..." << '\n';
	}
	catch (...) {
		cerr << "problems, problems, but: keep calm and carry on!\n";
	}

	for (auto &t : all_threads) {
		t.join();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}

