/*
 * Copyright (C) 2014 Nathan Bass <https://github.com/IngCr3at1on>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*******************************************************************************
SCE (Smart Chat Entity, pronounced C).

Used for concept testing.
*******************************************************************************/

#include <iostream>

#include "../lib/SCEEval.hpp"
#include "../lib/SCESocket.hpp"

bool running;
SCEEval _eval;
SCESocket _socket;

void *listen_console(void *dummy) {
	std::string input;
	std::cout << "# ";
	getline(std::cin, input);
	if(!input.empty())
	running = _eval.read_input(input, _socket, NONE);
}

void *listen_irc(void *dummy) {
	while(_socket.IRCConnected() && running)
		running = _eval.read_input(_socket.listen_irc(), _socket, IRC);
}

int execute() {
	pthread_t listen1, listen2;
	running = true;

	std::cout << "Console started.\n" << std::endl;
	
	while(running) {
		/* When I replace these w/ C++11 threads instead of pthreads the program
		 * fails during the sleep functions during the IRC connect function. */
		pthread_create(&listen1, NULL, listen_console, NULL);
		pthread_create(&listen2, NULL, listen_irc, NULL);

		pthread_join(listen1, NULL);
	}
	
	pthread_exit(NULL);
	return 0;
}

int main(int argc, char *argv[]) {
	running = false;

	return execute();
}
