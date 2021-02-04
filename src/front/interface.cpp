/*
* BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
* inspired by Debian's bible package
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

//Standard/STL includes
#include <iostream>
#include <string>
#include <list>

#include <sys/ioctl.h>
#include <unistd.h>

//SWORD Project includes
#include <swmgr.h>
#include <markupfiltmgr.h>

//Project includes
#include "interface.h"
#include "display.h"
#include "pager.h"
#include "../back/passage.h"
#include "../back/library.h"
#include "../back/parser.h"
#include "../back/types.h"
#include "../back/search.h"

void Interface::initalize() {
    configLines();

    std::cout  << "Initializing SWORD, please wait..." << std::endl;
    this->swordLibrary = new sword::SWMgr(new sword::MarkupFilterMgr
                                          (sword::FMT_PLAIN));
    
    library.setSwordLibrary(*swordLibrary);
    library.passage.setLibrary(*swordLibrary);    
    
    std::cout << "Initialized, proceeding to shell..." << std::endl;
}

void Interface::configLines() {
    uint maxLine = 1000;
    uint lineCount = 0;

    for(int i = maxLine; i >= 1; i--) {
        std::cout << i << std::endl;
    }

    std::cout << "Enter the number at the top of the screen: ";
    std::string input;
    std::getline(std::cin, input);

    lineCount = std::stoi(input);
    display.setSize(lineCount + 1);
}

validCommands Interface::processCommand(Command parsedCommand) {
    /*This is the basis of the main program loop. This evaluates parsedCommand
     * and then acts accordingly.
     */
    //TODO: Split this into functions

    Library library;
    Parser worksParser;

    validCommands commandPart;

    std::list<std::string> modules;

    commandPart = parsedCommand.commandPart;

    std::string tempBibles;
    std::string ref;
    std::string text;

    if(commandPart == cmdQuit) {
        //since we're quitting do nothing here
        return commandPart;
    } else if(commandPart == cmdShow) {
        int errSpaces = 0;

        if(parsedCommand.argumentPart.empty()) {
            display.displayHeader();
            std::cout <<  "No reference Specified";
            std::cout << std::endl;
            errSpaces++;
        } else {
            ref = parsedCommand.argumentPart.front();
        }

        if(selectedVersion == "") {
            errSpaces++;
            std::cerr <<  "Error: No version selected. (Try select)";
            std::cerr << std::endl;
            display.displaySpacer(errSpaces);
            return commandPart;
        }

       library.passage.setVersion(selectedVersion);
       
       text = library.passage.getText(ref);
       
       Pager textPager;
       std::list<page> pagedText;
       
       int termWidth;
       struct winsize termSize;
       ioctl(STDOUT_FILENO,TIOCGWINSZ,&termSize);
       termWidth = termSize.ws_col;
       

       textPager.setSize(display.getSize(),termWidth);
       pagedText = textPager.getPagedText(text);

       display.displayPages(pagedText);
       return commandPart;
    } else if(commandPart == cmdHelp) {
        display.displayHelp();
        return commandPart;
    } else if(commandPart == cmdList) {
        int numModules = 0;


        if(parsedCommand.argumentPart.front() == "bibles") {
            modules = library.getBibles();
        }
        else if (parsedCommand.argumentPart.front() == "commentaries") {
            modules = library.getCommentaries();
        }

        if(modules.empty()) {
            std::cerr <<  "No modules of type ";
            std::cerr <<  parsedCommand.argumentPart.front();
            std:: cerr << " found. Please install in another front-end.";
            std::cerr <<  std::endl;
            display.displaySpacer(1);
            return cmdError;
        }
        else {
            numModules = modules.size();
        }

        std::string curBible;

        while(!modules.empty()) {
            curBible = modules.front();
            std::cout <<  curBible;
            std::cout << std::endl;
            modules.pop_front();
        }

        display.displaySpacer(numModules);

        return commandPart;
    } else if (commandPart == cmdSelect) {
        //TODO: Stop assuming bibles here then handle actual arguments
        std::string selectedWork;

        if(parsedCommand.argumentPart.empty()) {
            std::cerr << "No module provided (Try list)" << std::endl;
            display.displaySpacer(1);
        }
        else {        
            selectedWork =  parsedCommand.argumentPart.front();
           
            //Check to make sure the module is, in fact, valid before 
            //continuing on to prevent crashing later
            //<fife>Nip it in the bud!</fife>
            if(library.isModuleValid(selectedWork)) {
                selectedVersion = selectedWork;
                display.displaySpacer();
            }
            else {
                //Module didn't come up, alert the user and bail out early.'
                std::cerr << "Module Name is invalid (Try list)" << std::endl;
                return commandPart;
            }
        }
        return commandPart;
    }
    else if(commandPart == cmdSearch) {
        if(selectedVersion != "") {

            Pager resultsPager;
            std::list<page> pagedResults;
            std::string results = "";
            std::string searchTerms = "";
            
            resultsPager.setSize(display.getSize());
            
            library.searcher.setModule(selectedVersion);
            library.searcher.setDisplay(display);
            
            //If no argument is provided to the command, prompt for the
            //search terms, otherwise recombine the arguments into a string
            if (parsedCommand.argumentPart.empty()) {
                display.displayHeader();
                display.displaySpacer(2);
                std::cout << "Enter a word or phrase to search for: ";
                std::getline(std::cin,searchTerms);

            }
            else {
                searchTerms = parsedCommand.argumentPart.front();
            }

            //TODO: Make this more than references or an option to do text or
            //reference results or both.
            results = library.searcher.search(searchTerms);
            pagedResults = resultsPager.getPagedText(results);
            
            display.clearScreen();
            display.displayHeader();
            display.displayPages(pagedResults);
            
            return commandPart;
        }
        else {
            std::cerr << "Error: No Module Selected" << std::endl;
            std::cerr << "Try select." << std::endl;
            return commandPart;
        }
    }
    else {
        //Invalid command head out.
        return cmdUnknown;
    }
}

int Interface::runInterface() {
    int returnCode = 0;
    std::string command = "";
    
    Parser commandParser;
    Command parsedCommand;
    
    //Initialize the interface
    initalize();
    display.clearScreen();
    display.displayHeader();
    display.displaySpacer();
    display.displayPrompt();
    std::getline(std::cin, command);
    
    parsedCommand = commandParser.parseCommand(command);

    //main program loop keep going until a quit command is given or an unrecoverable error thrown
    while(parsedCommand.commandPart != cmdQuit) {
        display.clearScreen();
        display.displayHeader();
        
        if(parsedCommand.commandPart == cmdUnknown) {
            std::cerr << "Error! invalid command! (Try ?)" << std::endl;
            display.displaySpacer(1);
        } else if(parsedCommand.commandPart == cmdError) {
            //Some error encountered. Since some are unrecoverable, Back out.
            std::cerr << "Unrecoverable error encountered Aborting..." << std::endl;
            returnCode = -1;
            break;
        }
        parsedCommand.commandPart = processCommand(parsedCommand);

        display.displayPrompt();
        std::getline(std::cin, command);
        parsedCommand = commandParser.parseCommand(command);
    }

    delete swordLibrary;
    return returnCode;
}
