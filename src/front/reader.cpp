/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2021  David Blue <yudahsshadow@gmx.com>
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "reader.h"

//STL includes
#include <string>
#include <list>

//SWORD includes
#include <swmgr.h>
#include <versekey.h>
#include <swmodule.h>
#include <swkey.h>

//Project includes
#include "pager.h"
#include "display.h"
#include "../back/passage.h"


void Reader::setDisplay( Display display ) {
    this->display = display;
}

void Reader::showText( std::string key ) {
    std::list<page> pagedText;
    std::string text;
    
    text = retrieveAllKeys(key);
    
    pager.setSize(display.getHeight(),display.getWidth());
    
    pagedText = pager.getPagedText(text);
    display.displayPages(pagedText);
}

void Reader::setModule( std::string module ) {
    selectedModule = module;
}

void Reader::setSwordLibrary(sword::SWMgr& library) {
    swordLibrary = library;
}

std::string Reader::retrieveAllKeys(std::string key) {
    std::string entries = "";
    sword::SWKey *moduleKey;
    sword::SWModule *module;
    
    module = swordLibrary.getModule(selectedModule.c_str());

    display.clearScreen();
    display.displayHeader();
    display.displaySpacer(1);
    std::cout << "Retrieving all module entries.. For large texts this may";
    std::cout << " take time";
    std::cout << std::endl;
    
    //TODO: instead of starting at top, start at entry with key
    for((*module) = sword::TOP; !module->popError(); (*module)++) {
        entries += module->getKeyText();
        entries += " ";
        entries += module->stripText();
        entries += "\n";
    }
    
    return entries;
}

