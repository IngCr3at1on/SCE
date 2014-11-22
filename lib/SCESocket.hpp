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
SCESocket: used as the base class for socker handler and all sub-sockets.
*******************************************************************************/

#ifndef _SCESOCKET_H_
#define _SCESOCKET_H_

enum socket_type {
	NONE,
	IRC,
};

class SCESocket {
	public:
		SCESocket() {
			admin = "IngCr3at1on";
		}
		virtual bool Init();
		virtual bool Connect();
		virtual bool Connected();
		virtual void Disconnect();
		virtual std::string Listen();

		virtual bool SendRaw(std::string /*data*/);
		virtual bool SendMsg(std::string /*dest*/, std::string /*message*/);

		virtual bool Login();
		virtual bool Quit(std::string /*msg*/);

		std::string admin;
};

#endif // _SCESOCKET_H_
