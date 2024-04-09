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
#include <string>
#include <list>

//Project Includes
#include "../front/pager.h"
#include "../back/parser.h"
#include "../back/types.h"



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
    uint lineCount = 0;
    uint colCount = 0;

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
        //Newlines appear within word groups and not always at EOL, so find them and
        //act accordingly.
        if(currentWord.find("\n") != std::string::npos) {
            int endlPos = 0;
            endlPos = currentWord.find("\n");
            if(endlPos != currentWord.back()) {
                //we've not got an EOL newline, so we need to split it again :/
                std::string preEndl = currentWord.substr(0, endlPos);
                //Check to see if we need to wrap before adding the newline.
                if(colCount + currentWord.length() +1 <= width) {
                    currentLine += preEndl + "\n";
                    currentPage.content += currentLine;
                    currentLine = "";
                    colCount = 0;
                    lineCount++;                    
                }
                else {
                    //We need to wrap before the newline, and start a new line
                    currentPage.content += currentLine + "\n";
                    currentLine = preEndl;
                }

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
            if(currentWord.find_first_not_of(" ") != std::string::npos) {
                currentLine += currentWord + " ";
            }
            else {
                currentLine += currentWord;
            }
            colCount += currentWord.length() + 1;
            currentWord = "";
            if(newLineCount > 0) {
                currentLine += "\n";
                currentPage.content += currentLine;
                currentLine = "";
                if(newLineCount > 1) {
                    currentLine += "\n";
                    currentPage.content += currentLine;
                    currentLine = "";
                }
                lineCount += newLineCount;
            }
        } else {
            //TODO: Do stuff about words that are by themselves longer than the
            //width.
            currentLine += "\n";
            currentPage.content += currentLine;
            currentLine = "";
            currentLine += currentWord + " ";
            colCount = currentWord.length() + 1;
            lineCount++;
        }

        if(lineCount >= pageSize - 3) {
            currentPage.lineCount = lineCount;
            pagedText.push_back(currentPage);
            currentPage.content = "";
            lineCount = 0;
            currentPage.lineCount = lineCount;
        }
    }

    //Check to see if we have any lines that didn't get pushed and flush them in
    if(currentLine.length() > 0) {
        currentPage.content += currentLine + "\n";
        currentLine = "";
        lineCount++;
    }

    if(currentPage.content.length() > 0) {
        currentPage.lineCount = lineCount;
        pagedText.push_back(currentPage);
        currentPage.content = "";
        lineCount = 0;
        currentPage.lineCount = lineCount;
    }

    return pagedText;
}

void Pager::setSize(uint rowSize, uint colSize) {
    this->lines = rowSize;
    this->cols = colSize;
}
