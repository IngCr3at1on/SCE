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
********************************************************************************
Socket handling, used to start individual protocol sockets.
*******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
// Lib files
#include "SCESocketHandler.hpp"
#include "InternalCommands/split.hpp"
// Include files
#include "rlutil/rlutil.h"

std::string SCESocketHandler::Listen() {
	std::string irc_buffer = _freenode.Listen();

	rlutil::setColor(rlutil::GREY);
	std::cout << irc_buffer << std::endl;
	rlutil::setColor(rlutil::WHITE);

	std::string input;
	std::istringstream iss(irc_buffer);
	if(getline(iss, input)) {
		if(input.find("\r") != std::string::npos)
			input = input.substr(0, input.size() - 1);
	}

	return input;
}

bool SCESocketHandler::Connect(SCESocket& socket) {
	if(socket.Init())
		return false;

	if(socket.Connected())
		return false;

	if(!socket.Connect())
		return false;
}

bool SCESocketHandler::Connected(SCESocket& socket) { return socket.Connected(); }

void SCESocketHandler::Disconnect(SCESocket& socket) { socket.Disconnect(); }

bool SCESocketHandler::Quit(SCESocket& socket) {
	if(socket.Connected()) {
		socket.Disconnect();
	}

	return true;
}
