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
SCESocketIRC, inherits SCESocket.hpp
*******************************************************************************/

#ifndef _SCESOCKETIRC_H_
#define _SCESOCKETIRC_H_

#include "SCESocket.hpp"

class SCESocketIRC : public SCESocket  {
	public:
		bool Connect();
		bool Connected();
		void Disconnect();
		std::string Listen();

		bool SendRaw(std::string /*data*/);
		bool SendMsg(std::string /*dest*/, std::string /*content*/);

		bool Login(std::string /*nick*/, std::string /*real*/);
		bool Quit(std::string /*msg*/);

		socket_type type;

	private:
		bool Init();

		std::string _nick;
		std::string _real;
};

#endif // _SCESOCKETIRC_H_
