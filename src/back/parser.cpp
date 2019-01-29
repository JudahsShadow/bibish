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

    //TODO: Find a better way for this corner case than to hard code it.
    if (tokenizedCommand.empty() && commandPart != "list"){
        argumentCount = 0;
        return parsedCommand;
    } else {
        //TODO: Fix the further conercasing this raises
        if (commandPart == "list" && tokenizedCommand.empty()) {
            //If we've gotten here we've encountered a list command with no
            //arguments, so make it bibles by default.
            argumentPart.push_back("bibles");
        }
        else {
            argumentPart = tokenizedCommand;
        }
    }

    if (commandPart == ("show")) {
        // TODO:Don't hardcode this  all we should have to parse is
        // making sure all the components of the argument
        // are one for passing back to the interface
        std::string reference = "";
        reference = this->detokenize(argumentPart);
        parsedCommand.push_back(reference);
    }
    else if (commandPart == "select") {
        //select has only one argument, stick it in line and ignore the rest
        parsedCommand.push_back(argumentPart.front());
    }
    else if (commandPart == "list") {
        if(argumentPart.front() == "bibles" ||
           argumentPart.front() == "commentaries" ||
           argumentPart.front() == "devotions" ||
           argumentPart.front() == "books" ||
           argumentPart.front() == "dictionaries") {

            parsedCommand.push_back(argumentPart.front());

        }
        else {
            //since list was given and the argument isn't another valid type
            //assume bibles
            parsedCommand.push_back("bibles");
        }
    }
    else if(commandPart == "search") {
        parsedCommand.push_back("search");
    }
    else {
        //Add a genral case to just pass arguments to the back as a list
        while(!argumentPart.empty()) {
            parsedCommand.push_back(argumentPart.front());
            argumentPart.pop_front();
        }
    }
    return parsedCommand;
}


std::list<std::string> Parser::tokenize(std::string string) {
  this->tokens.clear();
  if(string == "") {
      return this->tokens;
  } else {
      tokens = split(string);
      return this->tokens;
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

std::string Parser::detokenize(std::list< std::string > tokens) {
    std::string noTokens = "";

    if(tokens.empty()) {
        return noTokens;
    }
    else {
        noTokens = combine(tokens);
    }

    return noTokens;
}

std::string Parser::combine(std::list< std::string > stringList) {
    std::string combinedString = "";
    while(!stringList.empty()) {
        combinedString += stringList.front();
        combinedString += " ";
        stringList.pop_front();
    }
    return combinedString;
}
