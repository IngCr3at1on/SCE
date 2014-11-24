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

#include <cstdlib>
#include <iostream>
#include <string>
// Lib files
#include "SCESocket.hpp"
// Native files
#include "SCECommandEightball.hpp"

std::string SCECommandEightball::get_responses(std::vector<std::string> vec) {
	int rind = rand() % vec.size();
	return vec[rind];
}

void SCECommandEightball::CommandCall(
	std::string origin,
	std::string user,
	SCESocket& _socket,
	enum socket_type sock_type
	)
{
	std::vector<std::string> responses;
	responses.push_back("It is certain.");
	responses.push_back("Unlikely");
	responses.push_back("It is uncertain");
	responses.push_back("Signs point to yes.");
	responses.push_back("Try again later.");
	std::string msg = get_responses(responses);

	if(sock_type != NONE) {
		std::string dest;
		if(origin[0] == '#') dest = origin;
		else dest = user;

		_socket.SendMsg(dest, msg);
		return;
	}

	std::cout << msg << std::endl;
}
