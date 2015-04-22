﻿/*
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
#include <sys/types.h>

#include <swmgr.h>
#include <markupfiltmgr.h>

#include "interface.h"
#include "parser.h"
#include "display.h"
#include "../back/passage.h"
#include "../back/library.h"

void Interface::initalize() {
    configLines();
//     display.clearScreen();

    std::cout  << "Initalizing SWORD, please wait..." << std::endl;
    this->swordLibrary = new sword::SWMgr(new sword::MarkupFilterMgr
                                          (sword::FMT_PLAIN));
    std::cout << "Initalized, proceeding to shell..." << std::endl;
//     display.clearScreen();
}

void Interface::configLines() {
//     int colCount = 0;
    uint maxLine = 1000;
    uint lineCount = 0;

    for(int i = maxLine; i >= 1; i--) {
        std::cout << i << std::endl;
    }

    std::cout << "Enter the number at the top of the screen: ";
    std::string input;
    std::getline(std::cin, input);

    lineCount = atoi(input.c_str());
    display.setSize(lineCount + 1);
}

std::string Interface::processCommand(std::string command) {
    std::string validCommands[5];
    std::string text = "";
    std::string ref = "";

    Passage pass;
    Library library;
    Parser commandParser;
    Parser worksParser;

    std::string commandPart;

    std::list<std::string> bibles;
    std::list<std::string> parsedCommand;

    parsedCommand = commandParser.parseCommand(command);
    commandPart = parsedCommand.front();
    parsedCommand.pop_front();

    std::string tempBibles;

    validCommands[0] = "quit";
    validCommands[1] = "show";
    validCommands[2] = "?";
    validCommands[3] = "list";
    validCommands[4] = "select";

    if(commandPart == validCommands[0]) {
        return commandPart;

    } else if(commandPart == validCommands[1]) {
        pass.setLibrary(this->swordLibrary);
        int errSpaces = 0;

        if(parsedCommand.empty()) {
            display.displayHeader();
            std::cout <<  "No reference Specified";
            std::cout << std::endl;
//             display.displaySpacer(1);
            errSpaces++;
        } else {
            ref = parsedCommand.front();
        }

        if(selectedVersion == "") {
            errSpaces++;
            std::cerr <<  "Error: No version selected. (Try select)";
            std::cerr << std::endl;
            display.displaySpacer(errSpaces);
            return commandPart;
        }

        pass.setVersion(selectedVersion);

        text = pass.getText(ref);

        if(text == "-1") {
            //Module not found error clear out for now
            return "-2";
        }

        std::string dummy = "";
        display.displayHeader();
        std::cout << text << std::endl;
        display.displaySpacer(errSpaces);
        return commandPart;
    } else if(commandPart == validCommands[2]) {
        display.displayHelp();
        return commandPart;
    } else if(commandPart == validCommands[3]) {
        int numBibles = 0;

        library.setSwordLibrary(swordLibrary);
        tempBibles = library.getBibles();
        bibles = worksParser.tokenize(tempBibles);
        
        if(bibles.empty()) {
            std::cerr <<  "No bibles found, please install in another frontend";
            std::cerr <<  std::endl;
            display.displaySpacer(1);
            return "-3";
        }
        else {
            numBibles = 0;
        }
        
        std::string curBible;

        while(!bibles.empty()) {
            curBible = bibles.front();
            std::cout <<  curBible;
            std::cout << std::endl;
            bibles.pop_front();
        }

        display.displaySpacer(numBibles + 1);

        return commandPart;
    } else if (commandPart == validCommands[4]) {
        //TODO: Stop assuming bibles here then handle actual arguments
        std::string selectedWork;
       
        if(parsedCommand.empty()) {
            std::cerr << "No module provided (Try list)" << std::endl;
            display.displaySpacer(1);
        }
        else {
            selectedWork =  parsedCommand.front();
            selectedVersion = selectedWork;
        }
        return commandPart;
    }
    else {
        //Invalid command head out.
        return "-1";
    }
}

int Interface::runInterface() {
    int returnCode = 0;
    std::string command = "";

    //Initialize the interface
    initalize();
    display.clearScreen();
    display.displayHeader();
    display.displaySpacer();
    display.displayPrompt();
    std::getline(std::cin, command);

    //main program loop keep going until a quit command is given
    while(command != "quit") {
        display.clearScreen();
        display.displayHeader();
        command = processCommand(command);

        if(command == "-1") {
//             std::string dummy;

//             display.displayHeader();
            std::cerr << "Error! invalid command! (Try ?)" << std::endl;
            display.displaySpacer(1);
//             display.displayPrompt();
//             std::getline(std::cin, command);
        } else if(command == "-2") {
            //Specified module not found, since we can't install yet bail out
            std::cerr << "Module not found. Aborting.." << std::endl;
            returnCode = -1;
            break;
        } else if(command ==  "-3") {
            returnCode = -2;
            std::cerr <<  "No modules found. Aborting.." <<  std::endl;
            break;
        }

        display.displayPrompt();
        std::getline(std::cin, command);
    }

    delete this->swordLibrary;
    return returnCode;
}