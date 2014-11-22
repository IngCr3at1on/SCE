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
Socket Handler, inherits SCESocket and is used to start all sub sockets.
*******************************************************************************/

#ifndef _SCESOCKETHANDLER_H_
#define _SCESOCKETHANDLER_H_

#include "SCESocket.hpp"
#include "SCESocketHandler.hpp"
#include "SCESocketIRC.hpp"

class SCESocketHandler : public SCESocket {
	public:
		bool Connect(SCESocket& /*socket*/);
		bool Connected(SCESocket& /*socket*/);
		void Disconnect(SCESocket& /*socket*/);
		std::string Listen();

		bool Quit(SCESocket& /*socket*/);

		/* We can use a different socket for a different network, track by
		 * network name for ease. */
		SCESocketIRC _freenode;

	private:
		bool Init(SCESocket& /*socket*/);
};

#endif // _SCESOCKETHANDLER_H_
