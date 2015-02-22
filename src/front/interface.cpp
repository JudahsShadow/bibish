/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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
#include <iostream>
#include <string>

#include "interface.h"
#include "../back/passage.h"

// void Interface::() const
// {
//
// }

// void Interface::() const
// {
//
// }

void Interface::clearScreen() {
    int screenSize = 50; //current screen size?

    for (int i = 0; i <= screenSize; i++) {
        std::cout << std::endl;
    }
}

void Interface::showHeader() {
    std::cout << "Welcome to BIBISH" << std::endl;
}

void Interface::showPrompt() {
    std::cout << "Enter a command (? for help): ";
}

std::string Interface::processCommand (std::string command) {
    std::string validCommands[2];
    std::string text = "";
    std::string ref = "";
    int commandLength;
    Passage pass;
    validCommands[0] = "quit";
    validCommands[1] = "show";

    if (command == validCommands[0]) {
        return command;

    } else if (command.substr (0, 4) == validCommands[1]) {
        commandLength = command.length();
        ref = command.substr (5, command.length());
        pass.setVersion ("ESV");
        text = pass.getText (ref);

        if (text == "-1") {
            //Module not found error clear out for now
            return "-2";
        }

        std::string dummy = "";
        std::cout << text << std::endl;
        std::cout << "Press enter to continue";
        std::getline (std::cin, dummy);
        return command;

    } else {
        //Invalid command head out.
        return "-1";
    }
}

int Interface::runInterface() {
    int returnCode = 0;
    std::string command;
//Initialize the interface
    clearScreen();
    command = "";
    showHeader();
    showPrompt();
    std::getline (std::cin, command);

    //main program loop keep going until a quit command is given
    while (command != "quit") {
        command = processCommand (command);

        if (command == "-1") {
            std::string dummy;
            std::cerr << "Error! invalid command! (Try ?)" << std::endl;
            std::cout << "Press enter to try again." << std::endl;
            std::getline (std::cin, dummy);
        } else if (command == "-2") {
            //Specified module not found, since we can't install (yet bail out
            std::cerr << "Module not found. Aborting.." << std::endl;
            returnCode = -1;
            break;
        }

        clearScreen();
        showHeader();
        showPrompt();
        std::getline (std::cin, command);
    }

    return returnCode;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;