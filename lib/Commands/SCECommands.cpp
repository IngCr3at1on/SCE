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
SCECommands, manage all commands (for all sockets) from within here.
*******************************************************************************/

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

#include "../SCESocket.hpp"
#include "SCECommands.hpp"

#include "../../include/utils/clip.hpp"
#include "../../include/rlutil/rlutil.h"

// These will be removed.
const char *nick = "sce";
const char *real = "SCE, Smart Chat Entity";
const char *host = "irc.freenode.org";

int port = 6667;

void SCECommands::handle_command(
	std::string cmd,
	std::string origin,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	std::string admin_only = "This command is for admins only.";
	std::string original(cmd);
	std::string dest(user);
	if(origin[0] == '#') dest == origin;

	/* Chop the end off of our command for a more assured match on
	 * non-argumental commands. */
	std::string command = cmd.substr(0, cmd.find(" "));
	if(cmd.find(" ") != std::string::npos)
		clip(cmd);
	else
		cmd = "";

	// Keep in alpha!
	if(command.compare("connect") == 0) {
		if(sock_type == NONE)
			_socket.irc_connect(host, port, nick, real);
		
		return;
	}

	if(command.compare("IRC") == 0) {
		// Assign a return command.
		command = handle_irc_command(cmd, origin, user, _socket, sock_type);
		/* If the return command is empty return and continue listening
		 * otherwise process it through our standard command handler (without
		 * the IRC command type). */
		if(command.empty()) return;
	}

	if(command.compare("help") == 0) {
		Help(cmd, origin, user, _socket, sock_type);
		return;
	}

	if(command.compare("source") == 0) {
		_cmdsrc.CommandCall(origin, user, _socket, sock_type);
		return;
	}

	else if(sock_type == NONE) {
		std::cout << "Invalid command '" << original << "'.\n" << std::endl;
		Help("", "", "", _socket, sock_type);
	}
}

std::string SCECommands::handle_irc_command(
	std::string cmd,
	std::string dest,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	std::string admin_only = "This command is for admins only.";
	/* Chop the end off of our command for a more assured match on
	 * non-argumental commands. */
	std::string command = cmd.substr(0, cmd.find(" "));
	if(cmd.find(" ") != std::string::npos)
		clip(cmd);
	else
		cmd = "";

		// Keep in alpha!
	if(command.compare("join") == 0) {
		_ircjoin.CommandCall(cmd, dest, user, _socket, sock_type);
		return cmd = "";
	}

	if(command.compare("quit") == 0) {
		if(sock_type != NONE) {
			if(user.compare(_socket.admin) != 0) {
				_socket.IRCSendMsg(user, admin_only);
				return cmd = "";
			}
		}
		_socket.IRCQuit(cmd);
		return cmd = "";
	}

	return cmd;
}

void SCECommands::Help(
	std::string cmd,
	std::string dest,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	bool valid = false;
	std::string admin_only = "This command is for admins only.";
	std::string not_understanding = "I'm afraid I don't understand"; 
	/* Chop the end off of our command for a more assured match on
	 * non-argumental commands. */
	std::string command = cmd.substr(0, cmd.find(" "));

	if(cmd.find(" ") != std::string::npos)
		clip(cmd);
	else
		cmd = "";

	std::string msg;

	if(command.empty()) {
		valid = true;
		msg = "What would you like assistance with, commands perhaps?";
	}

	if(command.compare("commands") == 0) {
		valid = true;
		msg = HelpMsg;
		if(user.compare(_socket.admin) == 0 || sock_type == NONE) msg = AdmHelpMsg;
		if(sock_type == NONE) msg += "\n"+ConsoleHelpMsg;
	}

	if(command.compare("connect") == 0) {
		valid = true;
		if(sock_type == NONE)
			msg = "Connect to IRC.";
		else
			msg = not_understanding + ", a connection is already open.";
	}

	if(command.compare("IRC") == 0) {
		valid = true;
		if(cmd.empty())
			msg = "Command group, IRC:\nUsed to preface IRC specific commands.";

		if(cmd.compare("join") == 0) {
			if(user.compare(_socket.admin) == 0 || sock_type == NONE)
				msg = _ircjoin.AdmHelpMsg;
			else
				msg = _ircjoin.HelpMsg;
		}
		if(cmd.compare("quit") == 0) {
			if(user.compare(_socket.admin) == 0 || sock_type == NONE)
				msg = "Quit IRC with an optional message, usage: quit <message>";
			else
				msg = admin_only;
		}
	}

	if(!command.empty() && !valid) {
		msg = not_understanding + " '" + command + "'.";
	}

	if(sock_type != NONE) {
		if(dest[0] != '#') dest = user;
		_socket.IRCSendMsg(dest, msg);
		return;
	}
	std::cout << msg << std::endl;
}
