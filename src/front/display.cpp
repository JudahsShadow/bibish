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
#include "../back/types.h"

void Display::clearScreen() {
    for (int i = 0; i <= this->screenHeight; i++) {
        std::cout << std::endl;
    }
}

void Display::displayHeader() {
    std::cout << "Welcome to BIBISH" << std::endl;
}

void Display::displayPrompt() {
    std::cout << "Enter a command (? for help): ";
}

void Display::displaySpacer(int spacing) {
    for(int i = 1; i <= this->screenHeight - (spacing + 2); i++) {
        std::cout << std::endl;
    }
}

void Display::displayHelp() {
    clearScreen();
    displayHeader();
    std::cout << "Basic Commands are:" << std::endl;
    std::cout << "show [reference]" << std::endl;
    std::cout << "   Displays [reference] in the selected version";
    std::cout << std::endl;
    std::cout << "quit" << std::endl;
    std::cout << "   Exits the program" << std::endl;
    std::cout << "list [type]" << std::endl;
    std::cout << "   lists available modules of [type]" <<  std::endl;
    std::cout << "   defaults to bible if no type is specified" << std::endl;
    std::cout << "select [module]" << std::endl;
    std::cout << "   selects [module] to use for display with show command";
    std::cout << std::endl;
    std::cout << "?" << std::endl;
    std::cout << "   Shows this message" << std::endl;
    std::cout << "See README for more Commands" << std::endl;
    displaySpacer(13);
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
            std::cout << "Press enter for next page or q to quit: ";
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
    this->clearScreen();
    this->displayHeader();
    std::cout << "BIBISH Is [a] Bible Interactive SHell inspired by the bible package found in" << std::endl;
    std::cout << "Debian GNU/Linux." << std::endl;
    std::cout << "BIBISH is (C) 2015-2024 by David \"Judah\'s Shadow\" Blue." << std::endl;
    std::cout << "BIBISH is licensed under the GNU GPL Version 2.0 (GPL-2.0)." << std::endl;
    std::cout << "See the included COPYING and LICENSE files for more information" << std::endl;
    this->displaySpacer(5);
}
