/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2024  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

//STL Includes
#include <string>
#include <list>
#include <cstring>
#include <cctype>
#include <algorithm>

//SWORD Includes
#include <swmgr.h>
#include <swkey.h>

//Project Includes
#include "../back/gloss.h"


void Gloss::setSwordLibrary(sword::SWMgr *swordLib) {
    this->swordLibrary = swordLib;
}

void Gloss::setGlossary(std::string gloss) {
    this->glossary = this->swordLibrary->getModule(gloss.c_str());
}

std::string Gloss::getWord(std::string fromWord) {
    std::string toFrom;
    std::string entryText;
    std::string upperWord;

    std::transform(fromWord.begin(), fromWord.end(), fromWord.begin(),
                   [](unsigned char c) {return std::toupper(c);});

    if(this->glossary->getConfigEntry("GlossaryFrom") != NULL) {
        this->fromLang = this->glossary->getConfigEntry("GlossaryFrom");
    }

    if(this->glossary->getConfigEntry("GlossaryTo") != NULL) {
        this->toLang = this->glossary->getConfigEntry("GlossaryTo");
    }

    this->glossary->setKeyText(fromWord.c_str());

    entryText = this->glossary->stripText();

    toFrom = "From ";
    toFrom += this->fromLang;
    toFrom += " ";
    toFrom += this->glossary->getKeyText();
    toFrom += "\n";
    toFrom += "To ";
    toFrom += this->toLang;
    toFrom += " ";
    toFrom += entryText;

    return toFrom;

}
