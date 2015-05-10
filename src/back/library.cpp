/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
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

#include "library.h"

#include <string>

#include <swmgr.h>
#include <swmodule.h>

std::string Library::getBibles() {
    std::string moduleList = "";
    std::string bibleType = "Biblical Texts";
    std::string moduleType = "";
    sword::ModMap::iterator libraryIterator;

    for(libraryIterator = swordLibrary->Modules.begin();
            libraryIterator != swordLibrary->Modules.end();
            libraryIterator++) {

        sword::SWModule *tempMod = libraryIterator->second;
        moduleType = tempMod->getType();

        if(moduleType == bibleType) {
            moduleList += tempMod->getName();
            moduleList += " ";
        }
    }

    return moduleList;
}

void Library::setSwordLibrary(sword::SWMgr *library) {
    this->swordLibrary = library;
}
