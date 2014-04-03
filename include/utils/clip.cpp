/*
 * Copyright (C) 2013 Nathan Bass <https://github.com/IngCr3at1on>
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
/**
 * NICE : Nearly Intelligible Communications Entity
 * 
 * Clip the first word off the front of a string.
 */

#include <sstream>
#include <string>

#include "clip.h"

std::string clip(std::string &s) {
	std::stringstream stream(s);
	std::string::iterator it;
	std::string ret;

	// Iterate through our string to grab the first word in the stream.
	for(it = s.begin(); it != s.end(); it = s.begin()) {
		if(*it == ' ') {
			/* We hit a space so erase it but also break from our loop as we
			 * have our word. */
			s.erase(it);
			break;
		} else {
			/* Assign the next character in tmp to our iterator and delete the
			 * iterator from our str. */
			ret += *it;
			s.erase(it);
		}
	}
	// return our word.
	return ret;
}
