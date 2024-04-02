/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2024 its contributors. See CONTRIBUTORS file for more info
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef TYPES_H
#define TYPES_H

//STL Includes
#include <string>
#include <list>

//Keep this around in case it is decided to keep lines as lists of words
//instead of a block of text
// typedef std::list<std::string> line;
// typedef std::list<line> page;

typedef std::string line;

struct Page {
    int lineCount;
    line content;
};

//Create a page type of the preceding struct
typedef Page page;

/* Enumerated data type for commands. parseCommand in the Parser class
 * will take a command in, figure out what it is supposed to be based
 * on known localized equivalents to the commands.
 * Commands listed in an, as added order
 */
enum validCommands {
    cmdQuit,
    cmdList,
    cmdSelect,
    cmdSearch,
    cmdShow,
    cmdHelp,
    cmdRead,
    cmdAbout,
    cmdDevo,
    cmdGloss,
    cmdUnknown,
    cmdEmpty,
    cmdError
};

/* Struct for commands. This will allow for usage of the above
 * enumerated command type First part will be the enumerated
 * command part, second part will be a string list of arguments
 */
struct Command {
    validCommands commandPart;
    std::list<std::string> argumentPart;
};

typedef Command command;

//convenience type so the project doesn't have to depend on glibc
typedef unsigned int uint;
#endif // TYPES_H
