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
Help.
*******************************************************************************/

#include <iostream>
#include <string>

#include "../SCESocket.hpp"
#include "SCECommandHelp.hpp"

void SCECommandHelp::HelpMain(
	std::string dest,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	std::string msg = HelpMsg;
	if(user.compare(_socket.admin) == 0 || sock_type == NONE) msg = AdmHelpMsg;

	if(sock_type != NONE) {
		_socket.IRCSendMsg(dest, msg);
		return;
	}
	std::cout << msg << std::endl;
	std::cout << ConsoleHelpMsg << std::endl;
}

void SCECommandHelp::HelpCommand(
	std::string cmd,
	std::string dest,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	std::cout << "Individual command help not done yet." << std::endl;
	HelpMain(dest, user, _socket, sock_type);
}

void SCECommandHelp::CommandCall(
	std::string cmd,
	std::string origin,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	std::string dest = user;
	if(origin[0] == '#') dest == origin;
	
	if(cmd.empty()) {
		HelpMain(dest, user, _socket, sock_type);
		return;
	}

	HelpCommand(cmd, dest, user, _socket, sock_type);
}
