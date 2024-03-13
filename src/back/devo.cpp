/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2024  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

//SWORD Project Includes
#include <swmgr.h>
#include <swmodule.h>

//Project Includes
#include "../back/devo.h"
#include "../back/parser.h"

void Devo::setSwordLibrary(sword::SWMgr *swordLib) {
    this->swordLibrary = swordLib;
}

std::string Devo::getDevo(std::string date) {
    Parser dateParser;
    std::string parsedDate;
    std::string devo;
    sword::SWModule *devotion;

    devotion = this->swordLibrary->getModule(this->mod.c_str());

    parsedDate = dateParser.parseDate(date);

    devotion->setKey(parsedDate.c_str());

    devo = devotion->getKeyText();
    devo += "\n";
    devo += devotion->stripText();

    return devo;

}

void Devo::setDevotion(std::string module) {
    this->mod = module;
}
