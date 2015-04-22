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

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <list>

class Parser
{
public:
    Parser();
    ~Parser();
    int getNumberArguments();
    std::list<std::string> tokenize(std::string string);
    std::list<std::string> parseCommand(std::string command);
private:
    std::list<std::string> tokens;
    int argumentCount;
    
    std::list<std::string> split(std::string string);
};

#endif // PARSER_H
