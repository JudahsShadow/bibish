/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2024 its contributors. See CONTRIBUTORS file for more info
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
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

//STL/Standard Includes
#include <regex.h>
#include <string>
#include <iostream>

//SWORD Project Includes
#include <swmodule.h>
#include <swmgr.h>
#include <versekey.h>

//Project Includes
#include "../back/search.h"
#include "../back/types.h"

Display Search::searchDisplay;

void Search::setSwordLibrary(sword::SWMgr *library) {
    this->swordLibrary = library;
}

void Search::setModule(std::string mod) {
    this->module = this->swordLibrary->getModule(mod.c_str());
}

void Search::setDisplay(Display display) {
    this->searchDisplay = display;
}


void Search::percentUpdate(char percent, void *userData) {
    uint percentage;
    percentage = (int) percent;
    
    searchDisplay.displayPercentage(percentage);
}


std::string Search::search(std::string searchString) {
    sword::ListKey results;
    char lineLen = this->searchDisplay.getWidth();
    std::string verses = "";

    
    results = this->module->search(searchString.c_str(),
                                this->selectedSearchType,REG_ICASE, 0,0,
                                &percentUpdate,&lineLen);
    while(!results.popError()) {
        //TODO: Set this to return more than just verse references
        //or maybe make that a separate method?
        // verses = results.getElement()->userData;
        verses += (const char*)results;
        verses += "\n ";
        results++;
    }
    if(verses == "") {
        verses = "No results found\n";
    }
    return verses;

}

void Search::setSearchType(int searchType) {
    this->selectedSearchType = searchType;
}
