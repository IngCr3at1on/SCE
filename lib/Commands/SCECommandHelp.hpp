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

#ifndef _SCECOMMANDHELP_H_
#define _SCECOMMANDHELP_H_

#include "SCECommand.hpp"

class SCECommandHelp : public SCECommand {
	public:
		SCECommandHelp() {
			HelpMsg = "No user commands at this time.";
			AdmHelpMsg = "Current supported commands are:\nIRC join and quit.";
			ConsoleHelpMsg = "connect and exit are also supported locally in console.";
		}

		// Main call for all SCECommands.
		void CommandCall(
			std::string /*cmd*/,
			std::string /*origin*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);
	private:
		std::string ConsoleHelpMsg;

		void HelpMain(
			std::string dest,
			std::string user,
			SCESocket& _socket,
			enum socket_type sock_type
		);
		void HelpCommand(
			std::string cmd,
			std::string dest,
			std::string user,
			SCESocket& _socket,
			enum socket_type sock_type
		);
};

#endif // _SCECOMMANDHELP_H_
