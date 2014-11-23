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
Brain, used to process conversational data after it has been reviewed by eval
(for command regonition).
*******************************************************************************/

#ifndef _SCEBRAIN_H_
#define _SCEBRAIN_H_

#include "SCESocket.hpp"

class SCEBrain {
	public:
		void handle_speech(std::string /*data*/, std::string /*origin*/, std::string /*user*/, SCESocket& /*_socket*/);
};

#endif // _SCEBRAIN_H_
