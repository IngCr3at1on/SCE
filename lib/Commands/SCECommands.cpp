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

#include "SCECommands.hpp"

#include "../../include/utils/clip.hpp"
#include "../../include/rlutil/rlutil.h"

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
	if(command.compare("8ball") == 0 || command.compare("eightball") == 0) {
		_cmd8ball.CommandCall(origin, user, _socket, sock_type);
		return;
	}

	if(command.compare("cli") == 0) {
		_cmdcli.CommandCall(origin, user, _socket, sock_type);
		return;
	}

	if(command.compare("help") == 0) {
		Help(cmd, origin, user, _socket, sock_type);
		return;
	}

	if(command.compare("source") == 0) {
		_cmdsrc.CommandCall(origin, user, _socket, sock_type);
		return;
	}

	// Process group commands after generic.
	if(command.compare("IRC") == 0 || sock_type == IRC) {
		/* Treat all (non generic) commands passed on the IRC socket as IRC
		 * commands unless otherwise specified (Hipchat, JIM, etc (not sure
		 * this will quite work right when I add more sockets, needs further
		 * testing, consider first draft)). */
		if(command.compare("IRC") != 0)
			command = handle_irc_command(command+" "+cmd, origin, user, _socket, sock_type);
		else
			command = handle_irc_command(cmd, origin, user, _socket, sock_type);

		/* If the return command is empty return and continue listening
		 * otherwise process it through our standard command handler (without
		 * the IRC command type). */
		if(command.empty()) return;
	}

	if(sock_type == NONE)
		std::cout << "Invalid command '" << original << "'.\n" << std::endl;

	Help(cmd, origin, user, _socket, sock_type);
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

		// Keep in alpha!
	if(command.compare("connect") == 0) {
		if(sock_type == NONE)
			Handler._freenode.Connect();
		
		return cmd = "";
	}

	if(command.compare("join") == 0) {
		if(sock_type == NONE)
			_ircjoin.CommandCall(cmd, dest, user, Handler._freenode, sock_type);
		else
			_ircjoin.CommandCall(cmd, dest, user, _socket, sock_type);
		return cmd = "";
	}

	if(command.compare("leave") == 0 || command.compare("part") == 0) {
		if(sock_type == NONE)
			_ircpart.CommandCall(cmd, dest, user, Handler._freenode, sock_type);
		else
			_ircpart.CommandCall(cmd, dest, user, _socket, sock_type);
		return cmd = "";
	}

	if(command.compare("quit") == 0) {
		if(sock_type != NONE) {
			if(user.compare(_socket.admin) != 0) {
				_socket.SendMsg(user, admin_only);
				return cmd = "";
			}
		}
		if(sock_type == NONE)
			Handler._freenode.Quit(cmd);
		else
			_socket.Quit(cmd);
		return cmd = "";
	}

	return cmd;
}

void SCECommands::Help(
	std::string cmd,
	std::string origin,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
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

	bool valid = false;

	if(command.empty() || command.compare("me") == 0) {
		valid = true;
		msg = "What would you like assistance with, commands perhaps?";
	}

	if(command.compare("8ball") == 0 || command.compare("eightball") == 0) {
		valid = true;
		msg = _cmd8ball.HelpMsg;
	}

	if(command.compare("cli") == 0) {
		valid = true;
		msg = _cmdcli.HelpMsg;
	}

	if(command.compare("commands") == 0) {
		valid = true;
		msg = HelpMsg;
		if(user.compare(_socket.admin) == 0 || sock_type == NONE) msg = AdmHelpMsg;
		if(sock_type == NONE) msg += "\n"+ConsoleHelpMsg;
	}

	if(command.compare("IRC") == 0 || (sock_type == IRC && !command.empty())) {
		if(command.compare("IRC") != 0)
			cmd = command;

		if(cmd.empty()) {
			valid = true;
			msg = "Command group, IRC:\nUsed to preface IRC specific commands.";
		}

		if(command.compare("connect") == 0) {
			valid = true;
			if(sock_type == NONE)
				msg = "Connect to IRC.";
			else
				msg = not_understanding + ", a connection is already open.";
		}

		if(cmd.compare("join") == 0) {
			valid = true;
			if(user.compare(_socket.admin) == 0 || sock_type == NONE)
				msg = _ircjoin.AdmHelpMsg;
			else
				msg = _ircjoin.HelpMsg;
		}

		if(cmd.compare("leave") == 0 || cmd.compare("part") == 0) {
			valid = true;
			if(user.compare(_socket.admin) == 0 || sock_type == NONE)
				msg = _ircpart.AdmHelpMsg;
			else
				msg = _ircpart.HelpMsg;
		}

		if(cmd.compare("quit") == 0) {
			valid = true;
			if(user.compare(_socket.admin) == 0 || sock_type == NONE)
				msg = "Quit IRC with an optional message, usage: quit <message>";
			else
				msg = admin_only;
		}
	}

	if(command.compare("source") == 0) {
		valid = true;
		msg = _cmdsrc.HelpMsg;
	}

	if(!command.empty() && !valid) {
		msg = not_understanding + " '" + command + "'.";
	}

	if(sock_type != NONE) {
		_socket.SendMsg(user, msg);
		return;
	}
	std::cout << msg << std::endl;
}
