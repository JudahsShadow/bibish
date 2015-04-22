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

#include "pager.h"

#include "../front/parser.h"

#include <sys/types.h>
#include <string>
#include <list>


Pager::Pager()
{
    this->cols = 0;
    this->lines = 0;
}

// Pager::~Pager()
// {
//
// }

//This bad boy takes a raw string, and breaks it down into a list of
//of lists (pages) of strings (lines).
std::list< std::list<std::string> > Pager::getPagedText(std::string text) {
    uint width = this->cols;
    uint pageSize = this->lines;
    int pageCount = 0;
    int colCount = 0;
    
    Parser stringTokenizer;
    std::list<std::string> words;
    std::string currentWord;
    
    std::list<std::string> currentPage;
    std::list<std::list <std::string> > pagedText;
    
    words = stringTokenizer.tokenize(text);
    
    while(!words.empty()) {
        currentWord = words.front();
        words.pop_front();
        if(colCount + currentWord.length() + 1 <= width) {
            currentPage.push_back(currentWord);
            colCount += currentWord.length() + 1; //+1 for space
        } else {
            //TODO: Do stuff about words that are by themselves longer than
            //TODO the width.
            pagedText.push_back(currentPage);
            currentPage.clear();
            colCount = 0;
        }
    }
    
    return pagedText;
}

void Pager::setSize(uint rowSize, uint colSize) {
    this->lines = rowSize;
    this->cols = colSize;
}