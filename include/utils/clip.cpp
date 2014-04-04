/*
 Copyright (C) 2014 Nathan Bass <https://github.com/IngCr3at1on>
 
 MIT License (MIT):
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.

 GNU GPLv2 License:
 This program is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the
 Free Software Foundation; either version 2 of the License, or (at your
 option) any later version.
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.
 
 You should have received a copy of the GNU General Public License along
 with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*******************************************************************************
Clip the first word off the front of a string.
*******************************************************************************/

#include <sstream>
#include <string>

#include "clip.hpp"

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
