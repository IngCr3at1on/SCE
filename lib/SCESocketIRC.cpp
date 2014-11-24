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

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
// Lib files
#include "SCESocket.hpp"
#include "SCESocketIRC.hpp"
#include "InternalCommands/split.hpp"
// Include files
#include "rlutil/rlutil.h"
#include "sircsocket/IRCSocket.hpp"

const char *nick = "sce";
const char *real = "SCE, Smart Chat Entity";
const char *host = "irc.freenode.org";

int port = 6667;

std::string SCESocketIRC::Listen() {
	std::string buffer = sircsocket::ReceiveData();

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

bool SCESocketIRC::Init() {
	if(!sircsocket::Init()) {
		std::cout << "Unable to initialize IRC Socket." << std::endl;
		return false;
	}

	return true;
}

bool SCESocketIRC::Connect() {
	if(!Init())
		return false;

	if(Connected()) {
		std::cout << "IRCSocket already connected." << std::endl;
		return false;
	}

	if(sircsocket::Connect(host, port)) {
		std::cout << "Connected to " << host << " on " << port << "."
		<< std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(3));

		if(Login(nick, real)) {
			std::this_thread::sleep_for(std::chrono::seconds(9));
			return true;
		}

		if(sircsocket::Connected())
			sircsocket::Disconnect();
	}
	return false;
}

bool SCESocketIRC::Connected() { return sircsocket::Connected(); }

void SCESocketIRC::Disconnect() {
	sircsocket::Disconnect();
	std::cout << "IRCSocket disconnected." << std::endl;
}

bool SCESocketIRC::SendRaw(std::string data) {
	data.append("\n");

	rlutil::setColor(rlutil::DARKGREY);
	std::cout << data << std::endl;
	rlutil::setColor(rlutil::WHITE);

	return sircsocket::SendData(data.c_str());
}

bool SCESocketIRC::Login(std::string nick, std::string real) {
	_nick = nick;
	_real = real;

	if(SendRaw("NICK " + nick))
		if(SendRaw("USER " + nick + " 8 * :" + real))
			return true;
		
	return false;
}

bool SCESocketIRC::Quit(std::string msg) {
	if(!Connected())
		std::cout << "IRCSocket not connected." << std::endl;

	else {
		if(msg.empty()) msg = "goodbye.";
		SendRaw("QUIT :"+msg);
		Disconnect();
	}

	return true;
}

bool SCESocketIRC::SendMsg(std::string dest, std::string content) {
	std::vector<std::string> lines = split(content, '\n');
	int s = lines.size();
	for(int i = 0; i < s; i++)
		SendRaw("PRIVMSG " + dest + " :" + lines.at(i));
}
