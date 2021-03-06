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
Core Evaluation, determines if context of input (from console or socket) is a
command or part of a conversation.
*******************************************************************************/

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
// Native files
#include "SCEEval.hpp"
// Include files
#include "utils/utils.hpp"

bool SCEEval::read_input(std::string data, SCESocket& _socket, enum socket_type sock_type) {
	if(sock_type == IRC)
		return handle_irc(data, _socket);

	return handle_command(data, "", "", _socket, sock_type);
}

// In all cases return true unless you want to disconnect.
bool SCEEval::handle_command(
	std::string cmd,
	std::string origin,
	std::string user,
	SCESocket& _socket, 
	enum socket_type sock_type)
{
	std::string admin_only = "This command is for admins only.";

	if(cmd[0] == 's' && cmd[1] == 'c' && cmd[2] == 'e')
		cmd.erase(0,3);
	else if(sock_type == IRC && origin[0] == '#')
		goto finish_handle_speech;

	if(cmd.compare("exit") == 0 || cmd.compare(".exit") == 0) {
		if(sock_type != NONE) {
			if(user.compare(_socket.admin) != 0)
				_socket.SendMsg(user, admin_only);
			else
				_socket.SendMsg(user, "Exit is disabled outside of local terminal.");
			return true;
		}

		if(_socket.Connected()) {
			_socket.Quit("");
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		}

		return false;
	}

	if(cmd[0] == '.')
		// This is a command so remove the '.'
		cmd.erase(0,1);

	/* No command designation has been provided so assume this is either speech
	 * or not meant for SCE. */
	else if(sock_type != NONE)
		goto finish_handle_speech;

	// If our command returns true return without evaluating speach.
	if(_cmd.handle_command(cmd, origin, user, _socket, sock_type) == true)
		return true;

finish_handle_speech:
	// Only handle speech in designated channels.
	if(sock_type == IRC && (origin[0] == '#' && origin.compare("#projectopencannibal") != 0))
		return true;

	// Handle speech, always return true afterwards to continue listening.
	Brain.handle_speech(cmd, origin, user, _socket);
	return true;
}

bool SCEEval::handle_irc(std::string data, SCESocket& _socket) {
	std::string command;

	IRCMessage message = _irceval.Parse(data, _socket);
	command = message.command;
	/* If we got an error the socket has already been told to disconnect, we
	 * return true because we don't want to end the local command loop.
	 * 
	 * Ping responses are already handled in IRCEval so ignore them as well. */
	if(command.compare("PING") == 0 || command.compare("ERROR") == 0)
		return true;

	if(command.compare("PRIVMSG") == 0) {
		command = message.parameters.at(message.parameters.size() - 1);
		return handle_command(command, message.parameters.at(0), message.prefix.nick, _socket, IRC);
	}

	return true;
}
