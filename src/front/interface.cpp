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

//Standard/STL includes
#include <iostream>
#include <string>
#include <list>

//Linux includes to get terminal info such as screen size
#include <sys/ioctl.h>
#include <unistd.h>

//SWORD Project includes
#include <swmgr.h>
#include <markupfiltmgr.h>

//Project includes
#include "../front/interface.h"
#include "../front/display.h"
#include "../front/pager.h"
#include "../front/reader.h"
#include "../back/passage.h"
#include "../back/library.h"
#include "../back/parser.h"
#include "../back/types.h"
#include "../back/search.h"
#include "../back/lexicon.h"

void Interface::initalize() {
    this->configScreen();

    std::cout  << "Initializing SWORD, please wait..." << std::endl;
    this->swordLibrary = new sword::SWMgr(
                         new sword::MarkupFilterMgr(sword::FMT_PLAIN));
    
    this->library.setSwordLibrary(swordLibrary);
    this->library.passage.setLibrary(swordLibrary);
    this->library.lexicon.setSwordLibrary(swordLibrary);
    this->library.genbook.setSwordLibrary(swordLibrary);
    this->library.searcher.setSwordLibrary(swordLibrary);
    this->library.devotion.setSwordLibrary(swordLibrary);
    this->library.glossary.setSwordLibrary(swordLibrary);
    this->library.infoSys.setSwordLibrary(swordLibrary);
    
    std::cout << "Initialized, proceeding to shell..." << std::endl;
}

void Interface::configScreen() {
    struct winsize termSize;
    
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&termSize);
    
    this->display.setHeight(termSize.ws_row);
    this->display.setWidth(termSize.ws_col);
}

validCommands Interface::processCommand(Command parsedCommand) {
    /*This is the basis of the main program loop. This evaluates parsedCommand
    * and then acts accordingly.
    */

    validCommands commandPart;

    commandPart = parsedCommand.commandPart;

    if(commandPart == cmdQuit) {
        //since we're quitting do nothing here
        return commandPart;
    }
    else if(commandPart == cmdShow) {
        this->commandShow(parsedCommand);
        return commandPart;
    }
    else if(commandPart == cmdHelp) {
        if(parsedCommand.argumentPart.front() == "about" ||
           parsedCommand.argumentPart.front() == "About") {
            this->display.displayAbout();
            return commandPart;
        }
        else {
            this->display.displayHelp();
            return commandPart;
        }
    }
    else if(commandPart == cmdList) {
        commandList(parsedCommand);
        return commandPart;
    }
    else if (commandPart == cmdSelect) {
        this->commandSelect(parsedCommand);
        return commandPart;
    }
    else if(commandPart == cmdSearch) {
        if(selectedVersion != "") {
            this->commandSearch(parsedCommand);
            return commandPart;
        }
        else {
            std::cerr << "No Module Selected. Try select." << std::endl;
            this->display.displaySpacer();
            return commandPart;
        }
    }
    else if(commandPart == cmdRead) {
        this->commandRead(parsedCommand);
        return commandPart;
    }
    else if(commandPart == cmdAbout) {
        this->display.displayAbout();
        return commandPart;
    }
    else if(commandPart == cmdDevo) {
        this->commandDevo(parsedCommand);
        return commandPart;
    }
    else if(commandPart == cmdGloss) {
        this->commandGloss(parsedCommand);
        return commandPart;
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
    this->initalize();

    this->display.clearScreen();
    this->display.displayHeader();
    this->display.displaySpacer();
    this->display.displayPrompt();

    std::getline(std::cin, command);
    
    parsedCommand = commandParser.parseCommand(command);

    //main program loop keep going until a quit command is given or an
    //unrecoverable error thrown
    while(parsedCommand.commandPart != cmdQuit) {
        this->display.clearScreen();
        this->display.displayHeader();
        
        if(parsedCommand.commandPart == cmdUnknown) {
            std::cerr << "Error! invalid command! (Try ?)" << std::endl;
            this->display.displaySpacer(1);
        }
        else if(parsedCommand.commandPart == cmdError) {
            //Some error encountered. Since some are unrecoverable, Back out.
            std::cerr << "Unrecoverable error encountered Aborting...";
            std::cerr << std::endl;
            returnCode = -1;
            break;
        }

        parsedCommand.commandPart = processCommand(parsedCommand);

        this->display.displayPrompt();
        std::getline(std::cin, command);
        parsedCommand = commandParser.parseCommand(command);
    }

    delete swordLibrary;
    return returnCode;
}

void Interface::commandShow (Command parsedCommand) {
    int errSpaces = 0;
    Pager textPager;
    std::list<page> pagedText;
    std::string text; 
    std::string ref;

    
    if(parsedCommand.argumentPart.empty()) {
            this->display.displayHeader();
            std::cout <<  "No reference Specified";
            std::cout << std::endl;
            errSpaces++;
            this->display.displaySpacer(errSpaces);
            return;
    }
    else {
            ref = parsedCommand.argumentPart.front();
    }

    if(this->selectedVersion == "") {
        errSpaces++;
        std::cerr <<  "Error: No version selected. (Try select)";
        std::cerr << std::endl;
        this->display.displaySpacer(errSpaces);
        return;
    }
        
    std::string type = this->library.getModuleType(this->selectedVersion);
    if(type == "bible" || type =="commentary") {
        this->library.passage.setVersion(this->selectedVersion);
        text = this->library.passage.getText(ref);
    }
    else if(type == "lexdict") {
        this->library.lexicon.setDict(this->selectedVersion);
        text = this->library.lexicon.getEntry(ref);
    }
    else if(type == "book") {
        this->library.genbook.setModule(this->selectedVersion);

        if(ref == "toc"|| ref == "TOC") {
            std::cout << "Getting book Table of Contents (TOC) this may take";
            std::cout << "several moments depending on the size of the work.";
            std::cout << std::endl;

            text = this->library.genbook.getTOC();
        }
        else {
            text = this->library.genbook.getText(ref);
        }
    }
            
    
    textPager.setSize(this->display.getHeight(),this->display.getWidth());
    pagedText = textPager.getPagedText(text);

    this->display.displayPages(pagedText);
}

void Interface::commandList(Command parsedCommand) {
    std::list<std::string> modules;
    

    if(parsedCommand.argumentPart.front() == "bibles") {
            modules = this->library.getBibles();
        }
        else if (parsedCommand.argumentPart.front() == "commentaries") {
            modules = this->library.getCommentaries();
        }
        else if(parsedCommand.argumentPart.front() == "lexicons" ||
                parsedCommand.argumentPart.front() == "dictionaries") {
            modules = this->library.getLexicons();
        }
        else if(parsedCommand.argumentPart.front() == "book" ||
                parsedCommand.argumentPart.front() == "books") {
            modules = this->library.getGenBooks();
        }
        else if(parsedCommand.argumentPart.front() == "devotions") {
            modules = this->library.getDevotionals();
        }
        else if(parsedCommand.argumentPart.front() == "unorthodox") {
            modules = this->library.getUnorthodox();
        }
        else if(parsedCommand.argumentPart.front() == "glossaries") {
            modules = this->library.getGlossaries();
        }
        else if(parsedCommand.argumentPart.front() == "essays") {
            modules = this->library.getEssays();
        }

        if(modules.empty()) {
            std::cerr <<  "No modules of type ";
            std::cerr <<  parsedCommand.argumentPart.front();
            std::cerr << " found. Please install in another front-end.";
            std::cerr <<  std::endl;
            this->display.displaySpacer(1);
        }
        std::string curMod;
        std::string moduleList = "";
        Pager modulePager;
        std::list<page> modulePages;
        
        modulePager.setSize(this->display.getHeight(), this->display.getWidth());

        while(!modules.empty()) {
            curMod = modules.front();
            moduleList += curMod;
            moduleList += "\n";
            modules.pop_front();
        }
        modulePages = modulePager.getPagedText(moduleList);
        
        this->display.displayPages(modulePages);
}

void Interface::commandSelect(Command parsedCommand) {
    std::string selectedWork;

    if(parsedCommand.argumentPart.empty()) {
        std::cerr << "No module provided (Try list)" << std::endl;
        this->display.displaySpacer(1);
    }
    else {
        selectedWork =  parsedCommand.argumentPart.front();
        
        //Check to make sure the module is, in fact, valid before
        //continuing on to prevent crashing later
        //<fife>Nip it in the bud!</fife>
        if(this->library.isModuleValid(selectedWork)) {
            this->selectedVersion = selectedWork;
            this->display.displaySpacer();
        }
        else {
            //Module didn't come up, alert the user and bail out early.'
            std::cerr << "Module Name is invalid (Try list)" << std::endl;
            this->display.displaySpacer(1);
            return;
        }
    }

}

void Interface::commandSearch(Command parsedCommand) {
    Pager resultsPager;
    std::list<page> pagedResults;
    std::string results = "";
    std::string searchTerms = "";

    resultsPager.setSize(this->display.getHeight(),this->display.getWidth());

    this->library.searcher.setModule(this->selectedVersion);

    this->library.searcher.setDisplay(this->display);

    //If no argument is provided to the command, prompt for the
    //search type and terms, otherwise recombine the arguments into a string
    if (parsedCommand.argumentPart.empty() ||
        parsedCommand.argumentPart.front() == "") {
        this->display.displayHeader();
        std::cout << "1 - Exact Phrase" << std::endl;
        std::cout << "2 - Multi-word" << std::endl;
        std::cout << "3 - Regex (Advanced Option)" << std::endl;
        this->display.displaySpacer(3);
        std::cout << "Pick a search type: ";

        std::string choice;
        uint choiceNum;

        std::getline(std::cin,choice);
        choiceNum = std::stoi(choice);

        if(choiceNum == 1) {
            this->library.searcher.setSearchType(SEARCHTYPEEXACT);
        }
        else if(choiceNum == 2) {
            this->library.searcher.setSearchType(SEARCHTYPEMULTIWORD);
        }
        else if(choiceNum == 3) {
            this->library.searcher.setSearchType(SEARCHTYPEREGEX);
        }
        else {
            //If an invalid choice is made do multi-word
            this->library.searcher.setSearchType(SEARCHTYPEMULTIWORD);
        }

        this->display.clearScreen();
        this->display.displayHeader();
        this->display.displaySpacer();
        std::cout << "Enter a word or phrase to search for: ";
        std::getline(std::cin,searchTerms);

    }
    else {
        if(parsedCommand.argumentPart.front() == "multi") {
            this->library.searcher.setSearchType(SEARCHTYPEMULTIWORD);
            parsedCommand.argumentPart.pop_front();
        }
        else if(parsedCommand.argumentPart.front() == "exact") {
            this->library.searcher.setSearchType(SEARCHTYPEEXACT);
            parsedCommand.argumentPart.pop_front();
        }
        else if(parsedCommand.argumentPart.front() == "regex") {
            this->library.searcher.setSearchType(SEARCHTYPEREGEX);
            parsedCommand.argumentPart.pop_front();
        }
        else {
            //no or invalid search type given, assume multi-word
            this->library.searcher.setSearchType(SEARCHTYPEMULTIWORD);
        }
        searchTerms = parsedCommand.argumentPart.front();
    }

    //TODO: Make this more than references or an option to do text or
    //reference results or both.
    results = library.searcher.search(searchTerms);
    pagedResults = resultsPager.getPagedText(results);

    this->display.clearScreen();
    this->display.displayHeader();
    this->display.displayPages(pagedResults);

}

void Interface::commandRead(Command parsedCommand) {
    std::string reference;

    if(this->selectedVersion == "") {
        this->display.displayHeader();
        std::cerr << "No module selected. Try Select";
        std::cerr << std::endl;
        this->display.displaySpacer(1);
        return;
    }

    this->library.readMode.setDisplay(this->display);
    this->library.readMode.setSwordLibrary(this->swordLibrary);
    this->library.readMode.setModule(this->selectedVersion);

    reference = parsedCommand.argumentPart.front();
    this->library.readMode.showText(reference.c_str());
}

void Interface::commandDevo(Command parsedCommand) {
    Pager devotionPager;
    std::list<page> devotionPages;
    std::string devotionText;

    if(this->selectedVersion == "") {
        this->display.displayHeader();
        std::cerr << "No module selected. Try Select";
        std::cerr << std::endl;
        this->display.displaySpacer(1);
        return;
    }

    this->library.devotion.setDevotion(this->selectedVersion);

    devotionText = this->library.devotion.getDevo( \
    parsedCommand.argumentPart.front());

    devotionPager.setSize(this->display.getHeight(),this->display.getWidth());

    devotionPages = devotionPager.getPagedText(devotionText);

    this->display.displayPages(devotionPages);
}

void Interface::commandGloss(Command parsedCommand) {
    Pager glossaryPager;
    std::list<Page> glossPages;
    std::string word;
    std::string glossEntry;

    if(this->selectedVersion == "") {
        this->display.displayHeader();
        std::cerr << "No module selected. Try Select";
        std::cerr << std::endl;
        this->display.displaySpacer(1);
        return;
    }

    this->library.glossary.setGlossary(this->selectedVersion);

    word = parsedCommand.argumentPart.front();

    glossEntry = this->library.glossary.getWord(word);

    glossaryPager.setSize(this->display.getHeight(), this->display.getWidth());

    glossPages = glossaryPager.getPagedText(glossEntry);

    this->display.displayPages(glossPages);

}
