﻿/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2023  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

#ifndef LIBRARY_H
#define LIBRARY_H

//Standard/STL includes
#include <string>
#include <list>

//Sword includes
#include <swmgr.h>
#include <swmodule.h>

//Project includes
#include "passage.h"
#include "search.h"
#include "lexicon.h"

class Library {
    public:
        //Member objects for use externally (eg. library.passage.method())
        /* TODO: Decide if this will be top level, or if a modules object should
         * be included
         */
        Passage passage;
        Lexicon lexicon;
        Search searcher;

        std::list<std::string> getBibles();
        std::list<std::string> getCommentaries();
        std::list<std::string> getLexicons();
        std::list<std::string> getGenBooks();
        std::string getModuleType(std::string moduleName);
        bool isModuleValid(std::string module);
        void setSwordLibrary(sword::SWMgr *library);
    private:
        sword::SWMgr *swordLibrary;
        
        std::list<std::string> getModuleList(std::string moduleType);
};

#endif // LIBRARY_H
