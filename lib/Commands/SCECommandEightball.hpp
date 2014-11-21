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
Ask the magic eightball a question.
*******************************************************************************/

#ifndef _SCECOMMAND_EIGHTBALL_H_
#define _SCECOMMAND_EIGHTBALL_H_

#include <vector>

#include "SCECommand.hpp"

class SCECommandEightball : public SCECommand {
	public:
		SCECommandEightball() {
			HelpMsg = "Ask the magic eightball a question.";
		}
		// Main call for all SCECommands.
		void CommandCall(
			std::string /*origin*/,
			std::string /*user*/,
			SCESocket& /*_socket*/,
			enum socket_type /*sock_type*/
		);

	private:
		std::string get_responses(std::vector<std::string> /*vec*/);
};

#endif // _SCECOMMAND_EIGHTBALL_H_
