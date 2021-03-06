/*
 * Copyright (C) 2014 Nathan Bass <https://github.com/IngCr3at1on>
 * Copyright (C) 2011 Fredi Machado <https://github.com/Fredi>
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
IRC message evaluation
*******************************************************************************/

#include <algorithm>
#include <iostream>
#include <string>

#include "IRCEval.hpp"

IRCMessage IRCEval::Parse(std::string data, SCESocket& _socket) {
	std::string original(data);

	IRCCommandPrefix cmdPrefix;

	// if command has prefix
	if(data.substr(0, 1) == ":") {
		cmdPrefix.Parse(data);
		data = data.substr(data.find(" ") + 1);
	}

	std::string command = data.substr(0, data.find(" "));
	std::transform(command.begin(), command.end(), command.begin(), towupper);
	if(data.find(" ") != std::string::npos) {
		data = data.substr(data.find(" ") + 1);
	} else {
		data = "";
	}

	std::vector<std::string> parameters;
	
	if(data != "") {
		if(data.substr(0, 1) == ":") {
			parameters.push_back(data.substr(1));
		} else {
			size_t pos1 = 0, pos2;
			while ((pos2 = data.find(" ", pos1)) != std::string::npos) {
				parameters.push_back(data.substr(pos1, pos2 - pos1));
				pos1 = pos2 + 1;
				if(data.substr(pos1, 1) == ":") {
					parameters.push_back(data.substr(pos1 + 1));
					break;
				}
			}
			if(parameters.empty()) {
				parameters.push_back(data);
			}
		}
	}

	if(command == "ERROR") {
		/* This is already being passed to the terminal so no need to repeat it
		 * here. */
		_socket.Disconnect();
	}

	if(command == "PING")
		_socket.SendRaw("PONG :" + parameters.at(0));

	IRCMessage ircMessage(command, cmdPrefix, parameters);

	return ircMessage;
}
