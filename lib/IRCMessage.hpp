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
IRCMessage structure.
*******************************************************************************/

#ifndef _IRCMESSAGE_H
#define _IRCMESSAGE_H

#include <string>
#include <vector>

#include "InternalCommands/split.hpp"

struct IRCCommandPrefix {
	void Parse(std::string data) {
		if(data == "")
			return;

		prefix = data.substr(1, data.find(" ") - 1);
		std::vector<std::string> tokens;

		if(prefix.find("@") != std::string::npos) {
			tokens = split(prefix, '@');
			nick = tokens.at(0);
			host = tokens.at(1);
		}
		if(nick != "" && nick.find("!") != std::string::npos) {
			tokens = split(nick, '!');
			nick = tokens.at(0);
			user = tokens.at(1);
		}
	};

	std::string prefix;
	std::string nick;
	std::string user;
	std::string host;
};

struct IRCMessage {
	IRCMessage();
	IRCMessage(std::string cmd, IRCCommandPrefix p, std::vector<std::string> params) :
		command(cmd), prefix(p), parameters(params) {};

	std::string command;
	IRCCommandPrefix prefix;
	std::vector<std::string> parameters;
};

#endif // _IRCMESSAGE_H
