/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  David Blue <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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

#include "parser.h"

#include <list>
#include <string>
#include <sstream>

Parser::Parser() {

}

Parser::~Parser() {

}

int Parser::getNumberArguments() {
    return argumentCount;
}

std::list<std::string> Parser::tokenize(std::string string) {
  tokens.clear();
  tokens = split(string);
  
  return tokens;
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
      
      // do this even if we've already seen EOF.
      parts.push_back(token);
  }
  
  return parts;
  
}
