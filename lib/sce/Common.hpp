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
Common variables to be loaded into .cpp files only (no headers!)
*******************************************************************************/

#ifndef _SCE_COMMON_
#define _SCE_COMMON_

std::string admin_only = "This command is for admins only.";

/* These are not common but I figured this was a better place than where they
 * were, they will be removed. */
const char *nick = "sce";
const char *real = "SCE, Smart Chat Entity";
const char *host = "irc.freenode.org";

int port = 6667;

#endif // _SCE_COMMON
