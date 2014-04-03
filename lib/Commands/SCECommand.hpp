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
SCECommand base, extended by all SCECommands.
*******************************************************************************/

#ifndef _SCECOMMAND_H_
#define _SCECOMMAND_H_

class SCECommand {
	public:
		SCECommand() {
			HelpMsg = "A standard help message";
			AdmHelpMsg = "Administrator help message";
		}

		std::string HelpMsg;		// Standard help message.
		std::string AdmHelpMsg;		// Administrator help message.
};

#endif // _SCECOMMAND_H_
