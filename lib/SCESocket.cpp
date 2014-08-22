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
Socket handling, used to start individual protocol sockets.
*******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "SCESocket.hpp"
#include "split.hpp"

#include "../include/rlutil/rlutil.h"

std::string SCESocket::listen_irc() {
	std::string buffer = _irc.ReceiveData();

	rlutil::setColor(rlutil::GREY);
	std::cout << buffer << std::endl;
	rlutil::setColor(rlutil::WHITE);

	std::string input;
	std::istringstream iss(buffer);
	if(getline(iss, input)) {
		if(input.find("\r") != std::string::npos)
			input = input.substr(0, input.size() - 1);
	}

	return input;
}

bool SCESocket::Init() {
	if(_irc.Init()) {
		return true;
	}
	return false;
}

bool SCESocket::irc_connect(char const *host, int port, char const *nick,
	char const *real) {
	if(!Init())
		std::cout << "Unable to initialize Socket." << std::endl;

	if(IRCConnected())
		std::cout << "IRCSocket already connected." << std::endl;

	if(_irc.Connect(host, port)) {
		std::cout << "Connected to " << host << " on " << port << "."
		<< std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(3));

		if(IRCLogin(nick, real)) {
			std::this_thread::sleep_for(std::chrono::seconds(9));
			return true;
		}

		if(_irc.Connected())
			_irc.Disconnect();
	}
	return false;
}

void SCESocket::IRCDisconnect() {
	std::cout << "IRCSocket disconnected." << std::endl;
	_irc.Disconnect();
}

bool SCESocket::IRCSend(std::string data) {
	data.append("\n");

	rlutil::setColor(rlutil::DARKGREY);
	std::cout << data << std::endl;
	rlutil::setColor(rlutil::WHITE);

	return _irc.SendData(data.c_str());
}

bool SCESocket::IRCLogin(std::string nick, std::string real) {
	_nick = nick;
	_real = real;

	if(IRCSend("NICK " + nick))
		if(IRCSend("USER " + nick + " 8 * :" + real))
			return true;
		
	return false;
}

bool SCESocket::IRCQuit(std::string msg) {
	if(!IRCConnected())
		std::cout << "IRCSocket not connected." << std::endl;

	else {
		if(msg.empty()) msg = "goodbye.";
		IRCSend("QUIT :"+msg);
		IRCDisconnect();
	}

	return true;
}

bool SCESocket::IRCSendMsg(std::string dest, std::string content) {
	std::vector<std::string> lines = split(content, '\n');
	int s = lines.size();
	for(int i = 0; i < s; i++)
		IRCSend("PRIVMSG " + dest + " :" + lines.at(i));
}
