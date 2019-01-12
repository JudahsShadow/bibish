/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David Blue <yudahsshadow@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
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

#ifndef SEARCH_H
#define SEARCH_H

#include <string>

#include <swmgr.h>

#include "library.h"

class Search {
public:
    void setSwordLibrary(sword::SWMgr *library);
    void setModule(std::string module);

    std::string search(std::string searchString);
private:
    static void percentUpdate(char percent,void *userData);
    sword::SWMgr *swordLibrary;
    sword::SWModule *module;
};

#endif // SEARCH_H
