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
#include <iostream>

//Project Includes
#include "../front/display.h"
#include "../front/messages.h"
#include "../back/types.h"

void Display::clearScreen() {
    for (int i = 0; i <= this->screenHeight; i++) {
        std::cout << std::endl;
    }
}

void Display::displayHeader() {
    std::cout << msgHeader;
}

void Display::displayPrompt() {
    std::cout << msgPrompt;
}

void Display::displaySpacer(int spacing) {
    for(int i = 1; i <= this->screenHeight - (spacing + 2); i++) {
        std::cout << std::endl;
    }
}

void Display::displayHelp() {
    Pager helpPager;
    std::list<page> helpPages;

    std::string msgHelp = "Basic Commands are:\n";
    msgHelp += "show [reference]\n";
    msgHelp += "\tDisplays [reference] in the selected version\n";
    msgHelp += "quit\n";
    msgHelp += "\tExits the program\n";
    msgHelp += "list [type]\n";
    msgHelp += "\tlists available modules of [type]\n";
    msgHelp += "\tdefaults to bible if no type is specified\n";
    msgHelp += "select [module]\n";
    msgHelp += "\tselects [module] to use for display with show command\n";
    msgHelp += "?\n";
    msgHelp += "\tShows this message\n";
    msgHelp += "See README for more Commands\n";

    this->clearScreen();
    this->displayHeader();
    helpPager.setSize(this->screenHeight,this->screenWidth);
    helpPages = helpPager.getPagedText(msgHelp);
    this->displayPages(helpPages);
}

void Display::setHeight(uint size) {
    this->screenHeight = size;
}

uint Display::getHeight() {
    return this->screenHeight;
}
void Display::displayPages(std::list<page> text) {
    std::string displayText = "";
    page currentPage;
    uint numLines = 0;
    uint numPages = 0;

    while(!text.empty()) {

        displayText = "";
        currentPage = text.front();
        displayText = currentPage.content;
        numLines = currentPage.lineCount;
        numPages = text.size();
        
        std::cout << displayText;

        displaySpacer(numLines);
        text.pop_front();
        if(numPages > 1) {
            std::string dummy = "";
            std::cout << msgContinue;
            std::getline(std::cin,dummy);
            if(dummy == "q") {
                text.clear();
            }
            clearScreen();
            displayHeader();
        }
    }
}

void Display::displayPercentage(uint percent) {
    this->clearScreen();
    this->displayHeader();
    this->displaySpacer(0);
    std::cout << "Searching " << percent;
    std::cout << "% complete";
    std::flush(std::cout);
}

void Display::setWidth(uint size) {
    this->screenWidth = size;
}

uint Display::getWidth() {
    return this->screenWidth;
}

void Display::displayAbout() {
    Pager aboutPager;
    std::list<page> aboutPages;

    std::string msgAbout = "BIBISH version: ";
    msgAbout += msgVersion;
    msgAbout +="\n";
    msgAbout += "BIBISH Is [a] Bible Interactive SHell inspired by the bible";
    msgAbout += "package found in Debian GNU/Linux.\n";
    msgAbout += "BIBISH is (C) 2015-2024 by David \"Judah\'s Shadow\" Blue.\n";
    msgAbout += "BIBISH is licensed under the GNU GPL Version 2.0 (GPL-2.0).\n";
    msgAbout += "See the included COPYING and LICENSE files for more information\n";

    this->clearScreen();
    this->displayHeader();

    aboutPager.setSize(this->screenHeight, this->screenWidth);
    aboutPages = aboutPager.getPagedText(msgAbout);
    this->displayPages(aboutPages);
}
