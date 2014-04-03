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
IRC message evaluation
*******************************************************************************/

#ifndef _IRCEVAL_H
#define _IRCEVAL_H

#include "IRCMessage.hpp"
#include "../sce/SCESocket.hpp"

#include "Commands/IRCCommandJoin.hpp"

class IRCEval {
	public:
		IRCMessage Parse(std::string /*data*/, SCESocket& /*_socket*/);

		bool handle_command(
			std::string /*cmd*/,
			std::string /*origin*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);
	private:
		IRCCommandJoin _join;
};

#endif // _IRCEVAL_H
