/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2021-2024 its contributors. See CONTRIBUTORS file for more info
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//STL includes
#include <string>
#include <list>

//SWORD includes
#include <swmgr.h>
#include <versekey.h>
#include <swmodule.h>
#include <swkey.h>
#include <swbuf.h>

//Project includes
#include "../front/reader.h"
#include "../front/pager.h"
#include "../front/display.h"
#include "../back/passage.h"


void Reader::setDisplay(Display display) {
    this->display = display;
}

void Reader::showText(sword::SWBuf key) {
    std::list<page> pagedText;
    std::string text;
    
    text = this->retrieveAllKeys(key);
    
    this->pager.setSize(this->display.getHeight(),this->display.getWidth());
    
    pagedText = pager.getPagedText(text);
    this->display.displayPages(pagedText);
}

void Reader::setModule(std::string module) {
    this->selectedModule = module;
}

void Reader::setSwordLibrary(sword::SWMgr *library) {
    this->swordLibrary = library;
}

std::string Reader::retrieveAllKeys(sword::SWBuf key) {
    std::string entries = "";
    sword::VerseKey moduleKey;
    sword::SWModule *module;
    
    module = this->swordLibrary->getModule(selectedModule.c_str());
    
    this->display.clearScreen();
    this->display.displayHeader();
    this->display.displaySpacer(1);
    std::cout << "Retrieving all module entries.. For large texts this may";
    std::cout << " take time";
    std::cout << std::endl;

    if(key.size()) {
        for(module->setKeyText(key); !module->popError(); (*module)++) {
           entries += " ";
            entries += module->getKeyText();
            entries += " - ";
            entries += module->stripText();
        }        
    }
    else {
        for((*module) = sword::TOP; !module->popError();(*module)++) {
            entries += " ";
            entries += module->getKeyText();
            entries += " - ";
            entries += module->stripText();
        }
    }
    
    return entries;
}

