/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

#include "parser.h"

#include <list>
#include <string>
#include <sstream>

Parser::Parser() {
    argumentCount = 0;
}

Parser::~Parser() {

}

int Parser::getNumberArguments() {
    return argumentCount;
}

std::list< std::string > Parser::parseCommand(std::string command) {
    std::list<std::string> tokenizedCommand;
    std::string commandPart;
    std::list<std::string> argumentPart;
    std::list<std::string> parsedCommand;

    parsedCommand.clear();
    argumentPart.clear();

    tokenizedCommand = tokenize(command);

    commandPart = tokenizedCommand.front();
    tokenizedCommand.pop_front();

    parsedCommand.push_back(commandPart);

    if (tokenizedCommand.empty()) {
        argumentCount = 0;
        return parsedCommand;
    } else {
        argumentPart = tokenizedCommand;
    }

    if (commandPart == ("show")) {
        // TODO:Don't hardcode this  all we should have to parse is
        // making sure all the components of the argument
        // are one for passing back to the interface
        std::string reference = "";
        while (!argumentPart.empty()) {
            reference += argumentPart.front();
            argumentPart.pop_front();
        }
        parsedCommand.push_back(reference);
    }
    else if (commandPart == "select") {
        //select has only one argument, stick it in line and ignore the rest
        parsedCommand.push_back(argumentPart.front());
    }
    else {
        //Add a genral case to just pass arguments to the back.
        while(!argumentPart.empty()) {
            parsedCommand.push_back(argumentPart.front());
            argumentPart.pop_front();
        }
    }
    return parsedCommand;
}


std::list<std::string> Parser::tokenize(std::string string) {
  tokens.clear();
  if(string == "") {
      return tokens;
  } else {
      tokens = split(string);
      return tokens;
  }
}

std::list<std::string> Parser::split(std::string string) {
  std::istringstream tokenStream(string);
  std::list<std::string> parts;
  parts.clear();

  // The following algorithm is based on the one found at
  // http://www.cplusplus.com/faq/sequences/strings/split/#getline
  while (!tokenStream.eof()) {
      // Yes I know this is normally "The Wrong Way(TM)" to do this
      // since you shouldn't read past EOF, but getline is a bit
      // werid about spacings on stringstreams

      std::string token;
      std::getline(tokenStream, token, ' ');

      // do this even if we've already seen EOF. unless token is ""
      if( token != "") {
          parts.push_back(token);
      }
  }

  return parts;

}
