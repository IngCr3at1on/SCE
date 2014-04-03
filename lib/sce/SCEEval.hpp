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
Core evaluation, determines if context of input (from console or socket) is a
command or part of a conversation.
*******************************************************************************/

#ifndef _SCEEVAL_H_
#define _SCEEVAL_H_

#include "SCESocket.hpp"
#include "../irc/IRCEval.hpp"

#include "../Commands/SCECommandSource.hpp"

class SCEEval {
	public:
		bool read_input(std::string /*data*/, SCESocket& /*_socket*/, enum socket_type /*sock_type*/);

	private:
		IRCEval _irceval;
		SCECommandSource _cmdsrc;

		bool handle_command(
			std::string /*cmd*/,
			std::string /*origin*/,
			std::string /*user*/,
			SCESocket& /*_socket*/, 
			enum socket_type /*sock_type*/
		);

		bool handle_irc(std::string /*data*/, SCESocket& /*_socket*/);
		
}; // class SCEEval

#endif // _SCEEVAL_H_
