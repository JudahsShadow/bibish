/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2024 its contributors. See CONTRIBUTORS file for more info
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef PARSER_H
#define PARSER_H

//STL Includes
#include <string>
#include <list>

//Project Includes
#include "../back/types.h"

class Parser {
    public:
        Parser();
        ~Parser();
        int getNumberArguments();
        std::list<std::string> tokenize(std::string string);
        Command parseCommand(std::string command);
        std::string detokenize(std::list<std::string> tokens);
        std::string parseDate(std::string date);
        std::string parseConf(std::string text);
    private:
        std::list<std::string> tokens;
        uint argumentCount;

        std::list<std::string> split(std::string string);
        std::string combine(std::list<std::string> stringList);
};

#endif // PARSER_H
