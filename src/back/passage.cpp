/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015  David Blue <yudahsshadow@gmx.com>
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

void Passage::setVersion (std::string version) {
    this->version = version;
}

void Passage::setLibrary(sword::SWMgr library) {
  swordLibrary = library;
}

std::string Passage::getText (std::string reference) {
    std::string text = "";

    //Variables related to splitting up the reference for iteration
    sword::ListKey refRange;

    //Module variables
    sword::SWModule *module = \
        swordLibrary.getModule(version.c_str());
    sword::VerseKey key;


    refRange = key.parseVerseList(reference.c_str(), key, true);
    for(refRange = sword::TOP; !refRange.popError(); refRange++) {
        module->setKey(refRange);
        text += " "; //TODO: Fix this to show the book name on the first verse
        //TODO: show chap and verse only after the first verse
        text += module->getKeyText();
        text += " ";
        text += module->renderText();
    }

    return text;
}
