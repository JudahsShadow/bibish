/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

typedef Page page;



//convience type so the project doesn't have to depend on glibc
typedef unsigned int uint;
#endif // TYPES_H
