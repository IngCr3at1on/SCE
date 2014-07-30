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
Split a string into tokens based on a delimeter
	This has been separated from it's codebase (below) for easier usage.
		https://github.com/Fredi/IRCClient
*******************************************************************************/

#ifndef _SPLIT_H
#define _SPLIT_H

extern std::vector<std::string> split(std::string const& /*text*/, char /*sep*/);

#endif // _SPLIT_H
