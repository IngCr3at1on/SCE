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
Simple IRC Socket Handling:

	This has been pulled from https://github.com/Fredi/IRCClient for use in
	other IRC applications.

	For a full IRC Client or simple bot please see the above repo.

	All comments were added by me (Nathan) when updating for use as a library.
*******************************************************************************/

#ifndef _IRCSOCKET_H_
#define _IRCSOCKET_H_

// Moved all headers into .cpp file.

namespace simple_irc_socket {
	class IRCSocket{
		public:
			bool Init();
			bool Connect(char const */*host*/, int /*port*/);
			void Disconnect();
			bool Connected() { return _connected; }

			bool SendData(char const */*data*/);

			std::string ReceiveData();

		private:
			int _socket;
			bool _connected;
	}; // class IRCSocket
} // namespace simple_irc_socket

#endif // _IRCSOCKET_H_
