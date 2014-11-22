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
Leave/part an IRC channel.
*******************************************************************************/

#include <iostream>
#include <string>

#include "../SCESocket.hpp"
#include "IRCCommandPart.hpp"

void IRCCommandPart::CommandCall(
	std::string cmd,
	std::string origin,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	if(!_socket.Connected()) {
		std::cout << "IRCSocket not connected." << std::endl;
		return;
	}

	if(sock_type != NONE) {
		std::string dest;
		if(origin[0] == '#') dest = origin;
		else dest = user;

		if(user.compare(_socket.admin) != 0) {
			_socket.SendMsg(dest, HelpMsg);
			return;
		} else if(cmd.empty() || cmd[0] != '#') {
			_socket.SendMsg(dest, AdmHelpMsg);
			return;
		}
	}
	if(cmd.empty() || cmd[0] != '#') {
		std::cout << AdmHelpMsg << std::endl;
		return;
	}
	_socket.SendRaw("PART "+cmd);
}
