/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2023  David Blue <yudahsshadow@gmx.com>
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

#include "search.h"

#include <swmodule.h>
#include <swmgr.h>
#include <versekey.h>

#include <regex.h>
#include <string>
#include <iostream>

// Display Search::searchDisplay;

void Search::setSwordLibrary(sword::SWMgr *library) {
    swordLibrary = library;
}

void Search::setModule(std::string mod) {
    module = swordLibrary->getModule(mod.c_str());
}

void Search::setDisplay(Display display) {
    searchDisplay = display;
}


void Search::percentUpdate(char percent, void *userData) {
    //TODO: Hook this into the display class
    uint percentage;
    percentage = (int) percent;
    
    searchDisplay.displayPercentage(percent);
}


std::string Search::search(std::string searchString) {
    int searchType = -2; //multi- word is what we will use for now
    sword::ListKey results;
    char lineLen = 80;
    std::string verses = "";

    
    results = module->search(searchString.c_str(),searchType,
                            REG_ICASE, 0,0, &percentUpdate,
                            &lineLen);
    while(!results.popError()) {
        //TODO: Set this to return more than just verse references
        //or maybe make that a separate method?
        // verses = results.getElement()->userData;
      verses += (const char*)results;
      verses.append("\n");
    // std::cerr << (__u64)results.getElement()->userData;
      results++;
    }
    if(verses == "") {
        verses = "No results found\n";
    }
    return verses;

}


