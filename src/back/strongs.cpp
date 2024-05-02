/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2024 its contributors. See CONTRIBUTORS file for more info
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

//STL Includes
#include <string>

//SWORD Includes
#include <swmgr.h>
#include <swmodule.h>

//Project Includes
#include "../back/strongs.h"
#include "../back/search.h"

void Strongs::setSwordLibrary(sword::SWMgr *library) {
    this->swordLibrary = library;
}

void Strongs::setModule(std::string module) {
    this->mod = this->swordLibrary->getModule(module.c_str());
}

std::string Strongs::findStrongsNumber(std::string number) {
    std::string strongsRefs;

    if(!this->mod->getConfig().has("Feature","StrongsNumbers")) {
        strongsRefs = "Module does not support Strong's Numbers";
    }

    return strongsRefs;
}

std::string Strongs::findStrongsEntry(std::string word) {
    std::string strongsEntries;
    Search strongsSearcher;
    if(!this->mod->getConfig().has("Feature","GreekDef") &&
        !this->mod->getConfig().has("Feature","HebrewDef")) {
          strongsEntries = "Module is not a Greek/Hebrew Lexicon";
    }
    else {
        strongsSearcher.setSearchType(SEARCHTYPEMULTIWORD);
        strongsSearcher.setSwordLibrary(this->swordLibrary);
        strongsSearcher.setModule(this->mod->getName());
        strongsSearcher.setDisplay(this->searchDisplay);

        strongsEntries = strongsSearcher.search(word);
    }

    return strongsEntries;
}

void Strongs::setDisplay(Display display) {
    this->searchDisplay = display;
}
