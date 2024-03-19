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
#include <iostream>

//SWORD Project Includes
#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

//Project Includes
#include "../back/library.h"

std::list<std::string> Library::getBibles() {
    std::list<std::string> bibles;
    bibles = this->getModuleList("bible");
    return bibles;
}

std::list<std::string> Library::getCommentaries() {
    std::list<std::string> commentaries;
    commentaries = this->getModuleList("commentary");
    return commentaries;
}

std::list<std::string> Library::getLexicons() {
    std::list<std::string> lexicons;
    lexicons = this->getModuleList("dictionary");
    return lexicons;
}

std::list<std::string> Library::getGenBooks() {
    std::list<std::string> books;
    books = this->getModuleList("book");
    return books;
}

std::list<std::string> Library::getDevotionals() {
    std::list<std::string> devos;
    devos = this->getModuleList("devotion");
    return devos;
}

std::list<std::string> Library::getUnorthodox() {
    std::list<std::string> unorthodox;
    unorthodox = this->getModuleList("unorthodox");
    return unorthodox;
}


std::list<std::string> Library::getModuleList(std::string moduleType) {
    std::string module = "";
    sword::ModMap::iterator libraryIterator;
    std::list<std::string> moduleList;
    std::string selectedType;
    std::string modType;

    std::string bible = sword::SWMgr::MODTYPE_BIBLES;
    std::string comentary = sword::SWMgr::MODTYPE_COMMENTARIES;
    std::string devo = sword::SWMgr::MODTYPE_DAILYDEVOS;
    std::string book = sword::SWMgr::MODTYPE_GENBOOKS;
    std::string dict = sword::SWMgr::MODTYPE_LEXDICTS;

    std::string category = "";

    sword::SWModule *tempMod;

    if(moduleType == "bible") {
        selectedType = bible;
    }
    else if(moduleType == "commentary") {
        selectedType = comentary;
    }
    else if(moduleType == "devotion") {
            selectedType = devo;
    }
    else if(moduleType == "book") {
            selectedType = book;
    }
    else if(moduleType == "dictionary") {
            selectedType = dict;
    }
    else if(moduleType == "unorthodox") {
        selectedType = "cultish";
    }
    else {
            //We should never get here but you never know.
            module = "Invalid type";
            moduleList.push_back(module);
            return moduleList;
    }

    for(libraryIterator = this->swordLibrary->Modules.begin();
        libraryIterator != this->swordLibrary->Modules.end();
        libraryIterator++) {

        tempMod = libraryIterator->second;

        if(tempMod->getConfigEntry("Category") == NULL) {
            category = "";
        }
        else {
            category = tempMod->getConfigEntry("Category");
        }

        //Devotions will never match on straight type, so check category or
        //features and set the module type to devotion, otherwise accept the
        //type from the module.
        if(category == "Devotional" ||
            tempMod->getConfig().has("Feature","DailyDevotion")) {
            modType = devo;
        }
        //Modules with images aren't supported since this is a text only
        //application so set the type to something selectedType will never
        //match against
        else if(category == "Maps" || category == "Images" ||
            tempMod->getConfig().has("Feature", "Images")) {
            modType = "Unsupported";
        }
        else if(category == "Cults / Unorthodox / Questionable Material") {
            modType = "cultish";
        }
        else {
            modType = tempMod->getType();
        }


        if(modType == selectedType) {
            module = "For ";
            module += tempMod->getDescription();
            module += " select ";
            module += tempMod->getName();
            moduleList.push_front(module);
            module = "";
        }

    }

    return moduleList;

}


void Library::setSwordLibrary(sword::SWMgr *library) {
    this->swordLibrary = library;
}

bool Library::isModuleValid(std::string moduleName) {
    sword::SWModule *tmpMod;
    
    tmpMod = this->swordLibrary->getModule(moduleName.c_str());
    if(!tmpMod) {
        return false;
    }
    else {
        return true;
    }
}

std::string Library::getModuleType(std::string moduleName) {
    std::string modType;
    std::string engineType;
    sword::SWModule *module;
    
    module = this->swordLibrary->getModule(moduleName.c_str());
    engineType = module->getType();
    
    if(engineType == sword::SWMgr::MODTYPE_BIBLES) {
        modType = "bible";
    }
    else if(engineType == sword::SWMgr::MODTYPE_COMMENTARIES) {
        modType = "commentary";
    }
    else if(engineType == sword::SWMgr::MODTYPE_LEXDICTS) {
        modType = "lexdict";
    }
    else if(engineType == sword::SWMgr::MODTYPE_GENBOOKS) {
        modType = "book";
    }
    else {
        modType = "unsupported";
    }
    return modType;
}
