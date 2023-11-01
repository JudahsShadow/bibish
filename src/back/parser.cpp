/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2023  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

Command Parser::parseCommand(std::string command) {
    std::list<std::string> tokenizedCommand;
    std::string commandPart;
    std::list<std::string> argumentPart;
    Command parsedCommand;
    
    //Initalize the return value
    parsedCommand.commandPart = cmdEmpty;
    parsedCommand.argumentPart.clear();
    
    //Initialize the buffers
    argumentPart.clear();
    tokenizedCommand.clear();
    commandPart = "";

    tokenizedCommand = tokenize(command);
    if(!tokenizedCommand.empty()) {
        /*If after breaking the command into tokens we have something, as
         *opposed to nothing, put the first item in the commandPart variable
         *for testing against valid values
         */
        commandPart = tokenizedCommand.front();
        tokenizedCommand.pop_front();
    }
    else {
        commandPart = "";
        parsedCommand.commandPart = cmdEmpty;
    }

    //TODO: Find a better way for this corner case than to hard code it.
    if (tokenizedCommand.empty() && commandPart != "list") {
        argumentCount = 0;
    } else {
        //TODO: Fix the further corner-casing this raises
        if (commandPart == "list" && tokenizedCommand.empty()) {
            /* If we've gotten here we've encountered a list command with no
            * arguments, so make it bibles by default.
            */
            argumentPart.push_back("bibles");
            
        }
        else {
            argumentPart = tokenizedCommand;
        }
    }

    if (commandPart == ("show")) {
        // TODO:Don't hard-code this  all we should have to parse is
        // making sure all the components of the argument
        // are one for passing back to the interface
        std::string reference = "";
        reference = detokenize(argumentPart);
        parsedCommand.argumentPart.push_back(reference);
        parsedCommand.commandPart = cmdShow;
    }
    else if (commandPart == "select") {
        //select has only one argument, stick it in line and ignore the rest
        parsedCommand.argumentPart.push_back(argumentPart.front());
        parsedCommand.commandPart = cmdSelect;
    }
    else if (commandPart == "list") {
        if(argumentPart.front() == "bibles" ||
           argumentPart.front() == "commentaries" ||
           argumentPart.front() == "devotions" ||
           argumentPart.front() == "books" ||
           argumentPart.front() == "dictionaries" ||
            argumentPart.front() == "lexicons") {

            parsedCommand.argumentPart.push_back(argumentPart.front());
        }
        else {
            //since list was given and the argument isn't another valid type
            //assume bibles
            parsedCommand.argumentPart.push_back("bibles");
        }
        parsedCommand.commandPart = cmdList;
    }
    else if(commandPart == "search") {
        //For now, assume all arguments are part of tdhe search query
        //in the future look at this to parse actual command arguments when
        //those exist for search.
        std::string query = "";
        query = detokenize(argumentPart);
        parsedCommand.argumentPart.push_back(query);
        parsedCommand.commandPart = cmdSearch;
    }
    else if(commandPart == "quit") {
        parsedCommand.commandPart = cmdQuit;
    }
    else if(commandPart == "help" || commandPart == "?") {
        parsedCommand.commandPart = cmdHelp;
    }
    else if(commandPart == "read") {
        std::string reference;
        reference = detokenize(argumentPart);
        parsedCommand.argumentPart.push_back(reference);
        parsedCommand.commandPart = cmdRead;
    }
    else {
        //Add a general case to just pass arguments to the back as a list
        while(!argumentPart.empty()) {
            parsedCommand.argumentPart.push_back(argumentPart.front());
            argumentPart.pop_front();
        }
        parsedCommand.commandPart = cmdUnknown;
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
      // weird about spacing on stringstreams

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
