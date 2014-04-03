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
Socket Handling, used to start individual protocol sockets.
*******************************************************************************/

#ifndef _SCESOCKET_H_
#define _SCESOCKET_H_

#include "../../include/IRCSocket/IRCSocket.hpp"

using namespace simple_irc_socket;

enum socket_type {
	NONE,
	IRC,
};

class SCESocket {
	public:
		SCESocket() {
			admin = "IngCr3at1on";
		}

		bool irc_connect(char const */*host*/, int /*port*/, char const */*nick*/, char const */*real*/);
		bool IRCConnected() { return _irc.Connected(); }
		void IRCDisconnect();
		std::string listen_irc();

		bool IRCSend(std::string /*data*/);
		bool IRCSendMsg(std::string /*dest*/, std::string /*content*/);

		bool IRCLogin(std::string /*nick*/, std::string /*real*/);
		bool IRCQuit(std::string /*msg*/);

		std::string admin;

	private:
		IRCSocket _irc;

		std::string _nick;
		std::string _real;

		bool Init();
};

#endif // _SCESOCKET_H_
