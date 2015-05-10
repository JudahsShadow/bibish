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

#include <iostream>

#include "display.h"
#include "../back/types.h"

void Display::clearScreen() {
    for (int i = 0; i <= this->screenSize; i++) {
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
    for(int i = 1; i <= this->screenSize - (spacing + 2); i++) {
        std::cout << std::endl;
    }
}

void Display::displayHelp() {
    clearScreen();
    displayHeader();
    std::cout << "Valid Commands are:" << std::endl;
    std::cout << "show [reference]" << std::endl;
    std::cout << "Displays [reference] in the selected version" << std::endl;
    std::cout << "quit" << std::endl;
    std::cout <<  "list" << std::endl;
    std::cout <<  "lists available bibles" <<  std::endl;
    std::cout << "select [bible]" << std::endl;
    std::cout << "selects bible to use for showing references" << std::endl;
    std::cout << "Exits program" << std::endl;
    std::cout << "?" << std::endl;
    std::cout << "Shows this message" << std::endl;
    displaySpacer(11);
}

void Display::setSize(uint size) {
    screenSize = size;
}

uint Display::getSize() {
    return screenSize;
}
