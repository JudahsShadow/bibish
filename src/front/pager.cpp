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

#include "pager.h"

#include "../back/parser.h"
#include "../back/types.h"

#include <string>
#include <list>


Pager::Pager() {
    this->cols = 0;
    this->lines = 0;
}

Pager::~Pager() {

}

//This bad boy takes a raw string, and breaks it down into a list of
//of lists (pages) of strings (lines).
std::list<page> Pager::getPagedText(std::string text) {
    uint width = this->cols;
    uint pageSize = this->lines;
    int lineCount = 0;
    int colCount = 0;

    Parser stringTokenizer;
    std::list<std::string> words;
    std::string currentWord;

    line currentLine;
    page currentPage;
    std::list<page> pagedText;

    words = stringTokenizer.tokenize(text);

    while(!words.empty()) {
        currentWord = words.front();
        words.pop_front();

        if(currentWord == "\n") {
            //Flush the line if we encounter a newline in the text
            currentPage.push_back(currentLine);
            currentLine.clear();
            lineCount++;
            currentWord = "";
        }

        if(currentWord == "\n\n") {
            colCount = 0;
            currentPage.push_back(currentLine);
            currentLine.clear();
            currentLine.push_back(" ");
            currentPage.push_back(currentLine);
            lineCount += 2;
            currentLine.clear();
            currentWord = "";
        }

        if(currentWord.find("\n") != std::string::npos) {
            int endlPos = 0;
            endlPos = currentWord.find("\n");
            if(endlPos != currentWord.back()) {
                //we've not got a EOL newline, so we need to split it again :/
                std::string preEndl = currentWord.substr(0, endlPos);
                currentLine.push_back(preEndl);
                currentPage.push_back(currentLine);
                currentLine.clear();
                colCount = 0;
                lineCount++;

                std::string postEndl = currentWord.substr(endlPos + 1);
                currentWord = postEndl;
            }
        }

        if(colCount + currentWord.length() + 1 <= width) {
            int newLineCount = 0;
            int newLineLoc = 0;

            //check for EOL or double EOL at the end of words
            if(currentWord.find("\n") != std::string::npos) {
                newLineCount++;
                newLineLoc = currentWord.find("\n");
                currentWord.replace(newLineLoc,1,"");
                if(currentWord.find("\n") != std::string::npos) {
                    newLineCount++;
                    newLineLoc = currentWord.find("\n");
                    currentWord.replace(newLineLoc,1,"");
                }
            }
            currentLine.push_back(currentWord);
            colCount += currentWord.length() + 1; //+1 for space
            currentWord = "";
            if(newLineCount > 0) {
                currentPage.push_back(currentLine);
                currentLine.clear();
                if(newLineCount > 1) {
                    currentLine.push_back(" ");
                    currentLine.clear();
                }
                lineCount += newLineCount;
            }
        } else {
            //TODO: Do stuff about words that are by themselves longer than
            //TODO: the width.
            currentPage.push_back(currentLine);
            currentLine.clear();
            currentLine.push_back(currentWord);
            colCount = currentWord.length() + 1;
            lineCount++;
        }

        if(lineCount >= pageSize - 3) {
            pagedText.push_back(currentPage);
            currentPage.clear();
            lineCount = 0;
        }
    }

    //Check to see if we have any lines that didn't get pushed and flush them in
    if(currentLine.size() > 0) {
        currentPage.push_back(currentLine);
        currentLine.clear();
    }

    if(currentPage.size() > 0) {
        pagedText.push_back(currentPage);
        currentPage.clear();
        lineCount = 0;
    }

    return pagedText;
}

void Pager::setSize(uint rowSize, uint colSize) {
    this->lines = rowSize;
    this->cols = colSize;
}
