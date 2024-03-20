/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2024  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

//STL Includes
#include <list>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>

//Project Includes
#include "../back/parser.h"
#include "../back/types.h"


Parser::Parser() {
    this->argumentCount = 0;
}

Parser::~Parser() {

}

int Parser::getNumberArguments() {
    return this->argumentCount;
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

    tokenizedCommand = this->tokenize(command);
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

    if (tokenizedCommand.empty()) {
        argumentCount = 0;
    } else {
        argumentPart = tokenizedCommand;
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
           argumentPart.front() == "lexicons" ||
           argumentPart.front() == "unorthodox" ||
           argumentPart.front() == "glossaries") {

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
        //pass the argument part back to enable help for specific commands
        std::string arguments;
        arguments = this->detokenize(argumentPart);
        parsedCommand.argumentPart.push_back(arguments);
    }
    else if(commandPart == "read") {
        std::string reference;
        reference = this->detokenize(argumentPart);
        parsedCommand.argumentPart.push_back(reference);
        parsedCommand.commandPart = cmdRead;
    }
    else if(commandPart == "about") {
        parsedCommand.commandPart = cmdAbout;
    }
    else if(commandPart == "devo") {
        std::string date;
        parsedCommand.commandPart = cmdDevo;
        if(argumentPart.empty()) {
            date = "today";
        }
        else {
            date = this->detokenize(argumentPart);
        }
        parsedCommand.argumentPart.push_back(date);
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
      tokens = this->split(string);
      return tokens;
  }
}

std::list<std::string> Parser::split(std::string string) {
  std::istringstream tokenStream(string);
  std::list<std::string> parts;
  parts.clear();

  // The following algorithm is based on the one found at
  //http://www.cplusplus.com/faq/sequences/strings/split/#getline
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
        noTokens = this->combine(tokens);
    }

    return noTokens;
}

std::string Parser::combine(std::list< std::string > stringList) {
    std::string combinedString = "";
    while(!stringList.empty()) {
        combinedString += stringList.front();
        stringList.pop_front();
        //Only add a space if there are other items in the stringList
        if(!stringList.empty()) {
            combinedString += " ";
        }
    }
    return combinedString;
}

std::string Parser::parseDate(std::string date) {
    std::string parsedDate ="";
    std::string month;
    std::string day;
    std::list<std::string> tokenizedDate;

    //compute today's date for use with today and yesterday as an argument
    auto now = std::chrono::system_clock::now();
    std::time_t t_dateTime = std::chrono::system_clock::to_time_t(now);
    std::string dateTime = std::ctime(&t_dateTime);


    if(date == "today") {
        month = dateTime.substr(4,3);
        day = dateTime.substr(8,2);
    }
    else if(date == "yesterday") {
        uint numericDate;
        month = dateTime.substr(4,3);
        day = dateTime.substr(8,2);
        numericDate = std::stoi(day);
        numericDate--;
        if(numericDate < 10) {
            day = "0";
            day += std::to_string(numericDate);
        }
        else {
            day = std::to_string(numericDate);
        }
    }
    else if(date == "tomorrow") {
        uint numericDate;
        month = dateTime.substr(4,3);
        day = dateTime.substr(8,2);
        numericDate = std::stoi(day);
        numericDate++;
        if(numericDate < 10) {
            day = "0";
            day += std::to_string(numericDate);
        }
        else {
            day = std::to_string(numericDate);
        }
    }
    else {
        tokenizedDate = this->tokenize(date);
        //Assume we've been given a month and day separated by space'
        month = tokenizedDate.front();
        day = tokenizedDate.back();
    }

    if(month == "January" || month == "Jan") {
        parsedDate += "01.";
    }
    else if(month == "February" || month == "Feb") {
        parsedDate += "02.";
    }
    else if(month == "March" || month == "Mar") {
        parsedDate +=  "03.";
    }
    else if(month == "April" || month == "Apr") {
        parsedDate += "04.";
    }
    else if(month == "May") {
        parsedDate += "05.";
    }
    else if(month == "June" || month == "Jun") {
        parsedDate += "06.";
    }
    else if(month == "July" || month == "Jul") {
        parsedDate += "07.";
    }
    else if(month == "August" || month == "Aug") {
        parsedDate += "08.";
    }
    else if(month == "September" || month == "Sep") {
        parsedDate += "09.";
    }
    else if(month == "October" || month == "Oct") {
        parsedDate += "10.";
    }
    else if(month == "November" || month == "Nov") {
        parsedDate += "11.";
    }
    else if(month == "December" || month == "Dec") {
        parsedDate += "12.";
    }
    else {
        //We don't have a text month so just pass what we have along
        parsedDate += month;
        parsedDate += ".";
    }

    //For now assume the day portion is valid and add it in
    parsedDate += day;

    return parsedDate;
}
