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
SCECommands, manage all commands (non-socket specific) from within here.
*******************************************************************************/

#ifndef _SCECOMMANDS_H_
#define _SCECOMMANDS_H_

#include "SCECommand.hpp"
#include "SCECommandSource.hpp"

#include "IRCCommandJoin.hpp"

class SCECommands : public SCECommand {
	public:
		SCECommands() {
			HelpMsg = "No user commands at this time.";
			AdmHelpMsg = "Current supported commands are:\nIRC command group; join, quit.";
			ConsoleHelpMsg = "connect and exit.";
		}

		void handle_command(
			std::string /*cmd*/,
			std::string /*origin*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);

	private:
		std::string ConsoleHelpMsg;

		std::string handle_irc_command(
			std::string /*cmd*/,
			std::string /*dest*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);

		void Help(
			std::string /*cmd*/,
			std::string /*dest*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);

		SCECommandSource _cmdsrc;

		IRCCommandJoin _ircjoin;
};

#endif // _SCECOMMANDS_H_
