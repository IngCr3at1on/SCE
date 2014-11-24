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
// Lib files
#include "SCEEval.hpp"
#include "SCESocketHandler.hpp"
// Include files
#include "rlutil/rlutil.h"

static bool running;
static SCEEval Eval;
static SCESocketHandler Handler;

void listen_console() {
	std::string input;
	rlutil::setColor(rlutil::GREEN);
	std::cout << "SCE";
	rlutil::setColor(rlutil::LIGHTGREEN);
	std::cout << " # ";
	rlutil::setColor(rlutil::WHITE);
	rlutil::showcursor();
	getline(std::cin, input);

	SCESocket empty_socket;
	if(!input.empty())
		running = Eval.read_input(input, empty_socket, NONE);
}

void listen_freenode() {
	while(Handler._freenode.Connected() && running)
		running = Eval.read_input(Handler._freenode.Listen(), Handler._freenode, IRC);
}

int execute() {
	running = true;

	rlutil::hidecursor();
	std::cout << "SCE Console started.\n" << std::endl;
	
	while(running) {
		std::thread listen(listen_console);
		std::thread listen_irc_freenode(listen_freenode);

		// Wait for input so's to not loop for no raisin
		listen.join();
		// Detach to allow to run constantly
		listen_irc_freenode.detach();
	}

	return 0;
}

int main(int argc, char *argv[]) {
	running = false;

	return execute();
}
