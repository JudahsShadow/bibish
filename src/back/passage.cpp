/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David Blue <yudahsshadow@gmx.com>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "passage.h"
#include "library.h"

#include <string>
#include <iostream>
#include <list>

#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>
#include <versekey.h>
#include <listkey.h>

// void Passage::() const
// {
//
// }
//
// void Passage::() const
// {
//
// }

// void Passage::setReference(std::string reference) {
//     this->key = reference;
//     this->key.setKey(reference);
// }

void Passage::setVersion (std::string version) {
    this->version = version;
}

void Passage::setLibrary(sword::SWMgr *library) {\
  this->swordLibrary = library;
}

std::string Passage::getText (std::string reference) {
    std::string text = "";

    //Variables related to splitting up the reference for iteration
    sword::ListKey refRange;

    //Module variables
    sword::SWModule *module;
    sword::VerseKey key;
    
    module = this->swordLibrary->getModule(this->version.c_str());
    if(!module) {
        std::cerr << this->version;
        std::cerr << " not found, install it in another front-end";
        std::cerr << std::endl;
        text = "-1";
        return text;
    }

    refRange = key.parseVerseList(reference.c_str(), key, true);
    for (refRange = sword::TOP; !refRange.popError(); refRange++) {
        module->setKey (refRange);
        text += module->getKeyText();
        text += " ";
        text += module->renderText();
    }

    return text;
}
