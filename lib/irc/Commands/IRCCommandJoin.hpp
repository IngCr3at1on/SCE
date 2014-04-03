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
Join an IRC channel.
*******************************************************************************/

#ifndef _IRCCOMMANDJOIN_H_
#define _IRCCOMMANDJOIN_H_

#include "../../Commands/SCECommand.hpp"

class IRCCommandJoin : public SCECommand {
	public:
		IRCCommandJoin() {
			HelpMsg = "This command is for admins only.";
			AdmHelpMsg = "Join a channel, usage: join <channel>";
		}

		// Main call for all SCECommands.
		void CommandCall(
			std::string /*cmd*/,
			std::string /*origin*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);
};

#endif // _IRCCOMMANDJOIN_H_
