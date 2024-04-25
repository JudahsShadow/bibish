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

//SWORD Project Includes
#include <swmgr.h>
#include <swmodule.h>

//Project Includes
#include "../back/parser.h"
#include "../front/info.h"

void Info::setSwordLibrary(sword::SWMgr *library) {
    this->swordLibrary = library;
}

void Info::setModule(std::string module) {
    this->mod = this->swordLibrary->getModule(module.c_str());
}

std::string Info::getInfo() {
    std::string info;
    std::string description = "";
    std::string moduleVersion = "";
    std::string parsedDescription;
    Parser rtfParser;

    if(this->mod->getConfigEntry("About") != NULL) {
        description = this->mod->getConfigEntry("About");
        parsedDescription = rtfParser.parseConf(description);
        description = parsedDescription;
    }

    if(this->mod->getConfigEntry("Version") != NULL) {
        moduleVersion = this->mod->getConfigEntry("Version");
    }

    info += "Module Name: ";
    info += this->mod->getDescription();
    info += "\n";
    info += "Module Short Name: ";
    info += this->mod->getName();
    info += "\n";
    info += "Module Type: ";
    info += this->mod->getType();
    info += "\n";

    if(moduleVersion != "") {
        info += "Module Version: ";
        info += moduleVersion;
        info += "\n";
    }

    if(description != "") {
        info += "About: ";
        info += description;
        info += "\n";
    }

    return info;
}

std::string Info::getCopyright() {
    std::string copyrightInfo;
    std::string shortCopyrightInfo;
    std::string fullCopyrightInfo;
    std::string distroInfo;
    std::string parsedCopyright;
    Parser rtfParser;

    if(this->mod->getConfigEntry("ShortCopyright") != NULL) {
        shortCopyrightInfo = this->mod->getConfigEntry("ShortCopyright");
        parsedCopyright = rtfParser.parseConf(shortCopyrightInfo);
        copyrightInfo = parsedCopyright;
        copyrightInfo += "\n";
    }
    else if(this->mod->getConfigEntry("Copyright") != NULL) {
        fullCopyrightInfo = this->mod->getConfigEntry("Copyright");
        parsedCopyright = rtfParser.parseConf(fullCopyrightInfo);
        copyrightInfo += "Copyright: ";
        copyrightInfo += parsedCopyright;
        copyrightInfo += "\n";
    }
    else {
        copyrightInfo += "No copyright info found\n";
    }

    if(this->mod->getConfigEntry("DistributionLicense") != NULL) {
        distroInfo = this->mod->getConfigEntry("DistributionLicense");
        parsedCopyright = rtfParser.parseConf(distroInfo);
        copyrightInfo += "Distribution Terms: ";
        copyrightInfo += parsedCopyright;
        copyrightInfo += "\n";
    }
    else {
        copyrightInfo += "No distribution terms found\n";
    }

    return copyrightInfo;
}
