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
#include <iostream>
#include <string>
#include <list>

#include <swmgr.h>
#include <markupfiltmgr.h>

#include "interface.h"
#include "parser.h"
#include "../back/passage.h"
#include "../back/library.h"

// void Interface::() const
// {
//
// }

// void Interface::() const
// {
//
// }

void Interface::initalize() {
    configLines();
    clearScreen();

    std::cout  << "Initalizing SWORD, please wait..." << std::endl;
    this->swordLibrary = new sword::SWMgr(new sword::MarkupFilterMgr
                                          (sword::FMT_PLAIN));
    std::cout << "Initalized, proceeding to shell..." << std::endl;
    clearScreen();
}

void Interface::configLines() {
    int colCount = 0;
    int maxLine = 1000;
    int lineCount = 0;

    for(int i = maxLine; i >= 1; i--) {
        std::cout << i << std::endl;
    }

    std::cout << "Enter the number at the top of the screen: ";
    std::string input;
    std::getline(std::cin, input);

    lineCount = atoi(input.c_str());
    this->screenSize = lineCount + 1;
}


void Interface::clearScreen() {
    for (int i = 0; i <= this->screenSize; i++) {
        std::cout << std::endl;
    }
}

void Interface::displayHeader() {
    std::cout << "Welcome to BIBISH" << std::endl;
}

void Interface::displayPrompt() {
    std::cout << "Enter a command (? for help): ";
}

void Interface::displaySpacer(int spacing) {
    for(int i = 1; i <= this->screenSize - (spacing + 2); i++) {
        std::cout << std::endl;
    }
}

std::string Interface::processCommand (std::string command) {
    std::string validCommands[4];
    std::string text = "";
    std::string ref = "";

    Passage pass;
    Library library;
    Parser commandParser;
    Parser worksParser;

    int commandLength = command.length();
    std::list<std::string> bibles;

    std::string tempBibles;

    validCommands[0] = "quit";
    validCommands[1] = "show";
    validCommands[2] = "?";
    validCommands[3]  = "list";

    if (command == validCommands[0]) {
        return command;

    } else if (command.substr (0, 4) == validCommands[1]) {
        ref = command.substr (5, command.length());

        pass.setLibrary(this->swordLibrary);
        pass.setVersion ("ESV");
        text = pass.getText (ref);

        if (text == "-1") {
            //Module not found error clear out for now
            return "-2";
        }

        std::string dummy = "";
        clearScreen();
        displayHeader();
        std::cout << text << std::endl;
        //displaySpacer(10);
        std::cout << "Press enter to continue";
        std::getline (std::cin, dummy);
        return command;

    } else if(command == validCommands[2]) {
        displayHelp();
        return command;
        
    } else if(command.substr(0, 4) == validCommands[3]) {
        tempBibles = library.getBibles();
        std::string selectedBible = "";
        
        library.setSwordLibrary(swordLibrary);
        bibles = worksParser.tokenize(tempBibles);

        for(std::list<std::string>::iterator i = bibles.begin();
                i != bibles.end(); i++) {

        }

        clearScreen();
        displayHeader();
        return command;
    } else {
        //Invalid command head out.
        return "-1";
    }
}

void Interface::displayHelp() {
    clearScreen();
    displayHeader();
    std::cout << "Valid Commands are:" << std::endl;
    std::cout << "show reference" << std::endl;
    std::cout << "Displays the bible reference" << std::endl;
    std::cout << "quit" << std::endl;
    std::cout <<  "list" << std::endl;
    std::cout <<  "lists available bibles" <<  std::endl;
    std::cout << "Exits program" << std::endl;
    std::cout << "?" << std::endl;
    std::cout << "Shows this message" << std::endl;
    displaySpacer(6);
}

int Interface::runInterface() {
    int returnCode = 0;
    std::string command;

    //Initialize the interface
    initalize();
    clearScreen();
    command = "";
    displayHeader();
    displaySpacer();
    displayPrompt();
    std::getline (std::cin, command);

    //main program loop keep going until a quit command is given
    while (command != "quit") {
        command = processCommand (command);

        if (command == "-1") {
            std::string dummy;

            clearScreen();
            displayHeader();
            std::cerr << "Error! invalid command! (Try ?)" << std::endl;
            displaySpacer(1);
            std::cout << "Press enter to try again.";
            std::getline (std::cin, dummy);
        } else if (command == "-2") {
            //Specified module not found, since we can't install yet bail out
            std::cerr << "Module not found. Aborting.." << std::endl;
            returnCode = -1;
            break;
        }

        clearScreen();
        displayHeader();
        displaySpacer();
        displayPrompt();
        std::getline (std::cin, command);
    }

    clearScreen();
    delete this->swordLibrary;
    return returnCode;
}
