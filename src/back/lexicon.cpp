/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2021-2024  David Blue <yudahsshadow@gmx.com>
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


//STD and STL includes
#include <string>

//SWORD includes
#include <swkey.h>
#include <swbuf.h>
#include <swmodule.h>

//Project Includes
#include "../back/lexicon.h"

std::string Lexicon::getEntry(std::string entry) {
    std::string lexEntry;
    sword::SWKey lexKey;
    sword::SWModule *module ;
    
    module = this->swordLibrary->getModule(this->lexiDict.c_str());
    module->setKeyText(entry.c_str());
    
    lexEntry = module->getKeyText();
    lexEntry += module->renderText();    

    return lexEntry;
}

void Lexicon::setDict(std::string module) {
    this->lexiDict = module;
}


void Lexicon::setSwordLibrary(sword::SWMgr *swordLib) {
    this->swordLibrary = swordLib;
}

