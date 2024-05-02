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

//STL Includes
#include <list>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <clocale>
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
        std::string reference = "";

        reference = detokenize(argumentPart);

        parsedCommand.argumentPart.push_back(reference);
        parsedCommand.commandPart = cmdShow;
    }
    else if (commandPart == "select") {
        //select has only one argument, stick it in line and ignore the rest
        if (!argumentPart.empty()) {
            parsedCommand.argumentPart.push_back(argumentPart.front());
        } else {
            parsedCommand.argumentPart.push_back("");
        }
        parsedCommand.commandPart = cmdSelect;
    }
    else if (commandPart == "list") {
        if(!argumentPart.empty() &&
          (argumentPart.front() == "bibles" ||
           argumentPart.front() == "commentaries" ||
           argumentPart.front() == "devotions" ||
           argumentPart.front() == "books" ||
           argumentPart.front() == "dictionaries" ||
           argumentPart.front() == "lexicons" ||
           argumentPart.front() == "unorthodox" ||
           argumentPart.front() == "glossaries" ||
           argumentPart.front() == "essays")) {

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
        //Check the first part of the argument. If it's there and either multi
        //or exact (search types) push that on the argument list and proceed
        //with assuming the rest is the search query
        if(!argumentPart.empty() &&
            (argumentPart.front() == "multi" ||
            argumentPart.front() == "exact" ||
            argumentPart.front() == "regex")) {

            parsedCommand.argumentPart.push_front(argumentPart.front());
            argumentPart.pop_front();
        }
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
    else if(commandPart == "gloss") {
        std::string word;

        //Take the first "token" as the word and ignore everything else
        if(!argumentPart.empty()) {
            word = argumentPart.front();
        } else {
            word = "";
        }

        parsedCommand.commandPart = cmdGloss;

        parsedCommand.argumentPart.push_back(word);
    }
    else if(commandPart == "info") {
        parsedCommand.commandPart = cmdInfo;

        //Check the argument(s) for a valid subtype of info
        //Currently copyright and pass it on, otherwise ignore everything
        if(!argumentPart.empty() &&
            argumentPart.front() == "copyright") {
            parsedCommand.argumentPart.push_back(argumentPart.front());
        }
        else {
            parsedCommand.argumentPart.push_back("");
        }
    }
    else if(commandPart == "strongs") {
        parsedCommand.commandPart = cmdStrongs;

        if(!argumentPart.empty()) {
            std::string firstArg;

            firstArg = argumentPart.front();
            if(firstArg.find_first_of("G0") != std::string::npos ||
                firstArg.find_first_of("H0") != std::string::npos) {
                //First argument looks like a strongs number so push it
                //on the argument list for searching.
                parsedCommand.argumentPart.push_front(firstArg);
            }
            else {
                //We dont' have a strong's number so detokenize everything
                //to search the lexicon for the word(s)
                firstArg = this->detokenize(argumentPart);
                parsedCommand.argumentPart.push_back(firstArg);
            }
        }
        else {
            parsedCommand.argumentPart.push_back("");
        }
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

  //The following algorithm is based on the one found at
  //http://www.cplusplus.com/faq/sequences/strings/split/#getline
  while (!tokenStream.eof()) {
    //Yes I know this is normally "The Wrong Way(TM)" to do this
    //since you shouldn't read past EOF, but getline is a bit
    //weird about spacing on stringstreams

    std::string token;
    std::getline(tokenStream, token, ' ');


    // do this even if we've already seen EOF. unless token is ""
    if(token != "") {
        parts.push_back(token);
    }
  }

  return parts;

}

std::string Parser::detokenize(std::list<std::string> tokens) {
    std::string noTokens = "";

    if(tokens.empty()) {
        return noTokens;
    }
    else {
        noTokens = this->combine(tokens);
    }

    return noTokens;
}

std::string Parser::combine(std::list<std::string> stringList) {
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

    //If we have today, tomorrow, or yesterday calculate the current date and
    //handle accordingly
    if(date =="today" || date == "tomorrow" || date == "yesterday") {
        uint numericDate;

        auto now = std::chrono::system_clock::now();
        std::time_t t_dateTime = std::chrono::system_clock::to_time_t(now);
        std::string dateTime = std::ctime(&t_dateTime);

        //We are only interested in the 3 letter month and the 2 digit day out
        //of the date stamp, pull those out of the timestamp string
        month = dateTime.substr(4,3);
        day = dateTime.substr(8,2);

        //Make the date a uint to increment and decrement
        numericDate = std::stoi(day);

        if(date == "yesterday") {
            numericDate--;
        }
        else if(date == "tomorrow") {
            numericDate++;
        }

        //If the uint date is < 10 add a padding 0 at the front to conform with
        //the module key
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

std::string Parser::parseConf(std::string text) {
    std::string parsedText;
    std::string rtfNewLine = "\\par";
    std::string nextPara = "\\pard";
    std::string aHref = "<a href=\"";
    std::string endOpen = "\">";
    std::string closeTag = "</a>";
    std::string alignCenter = "\\qc";
    std::size_t matchPos;

    //Strip out centering for now.
    //TODO: Actually center the text
    matchPos = text.find(alignCenter);
    while(matchPos != std::string::npos) {
        text.replace(matchPos,3,"");
        matchPos = text.find(alignCenter);
    }

    //RTF specs use \pard to indicate the next paragraph should be styled
    //normally, we don't do any styling so strip these out first to prevent
    //the nexxt loop from turning them into \nd
    matchPos = text.find(nextPara);
    while(matchPos != std::string::npos) {
        text.replace(matchPos,5,"");
        matchPos = text.find(nextPara);
    }

    //\par is a paragraph marker in the RTF specs that conf modules can use.
    //Go through the provided string and turn any remaining \par to \n.
    matchPos = text.find(rtfNewLine);
    while(matchPos != std::string::npos) {
        text.replace(matchPos,4,"\n");
        matchPos = text.find(rtfNewLine);
    }

    //Strip out any <a href=" found in the conf text
    matchPos = text.find(aHref);
    while(matchPos != std::string::npos) {
        text.replace(matchPos,9,"");
        matchPos = text.find(aHref);
    }

    //Strip out the end of any anchor tags and replace with a space
    matchPos = text.find(endOpen);
    while(matchPos != std::string::npos) {
        text.replace(matchPos,2," ");
        matchPos = text.find(endOpen);
    }

    //Strip out any closing tags from anchors
    matchPos = text.find(closeTag);
    while(matchPos != std::string::npos) {
        text.replace(matchPos,4,"");
        matchPos = text.find(closeTag);
    }

    parsedText = text;

    return parsedText;
}
