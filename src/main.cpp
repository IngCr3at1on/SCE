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
#include <thread>

#include "../lib/SCEEval.hpp"
#include "../lib/SCESocket.hpp"

#include "../include/rlutil/rlutil.h"

static bool running;
static SCEEval _eval;
static SCESocket _socket;

void listen_console() {
	std::string input;
	rlutil::setColor(rlutil::GREEN);
	std::cout << "SCE # ";
	rlutil::setColor(rlutil::WHITE);
	rlutil::showcursor();
	getline(std::cin, input);
	if(!input.empty())
		running = _eval.read_input(input, _socket, NONE);
}

void listen_irc() {
	while(_socket.IRCConnected() && running)
		running = _eval.read_input(_socket.listen_irc(), _socket, IRC);
}

int execute() {
	running = true;

	rlutil::hidecursor();
	rlutil::setColor(rlutil::GREEN);
	std::cout << "SCE Console started.\n" << std::endl;
	
	while(running) {
		std::thread listen1(listen_console);
		std::thread listen2(listen_irc);

		// Wait for input so's to not loop for no raisin
		listen1.join();
		// Detach to allow to run constantly
		listen2.detach();
	}

	return 0;
}

int main(int argc, char *argv[]) {
	running = false;

	return execute();
}
