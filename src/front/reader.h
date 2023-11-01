/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2021-2023  David Blue <yudahsshadow@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef READER_H
#define READER_H

//STL Includes
#include <list>
#include <string>

//SWORD includes
#include <swmgr.h>
#include <swbuf.h>

//Project Includes
#include "display.h"
#include "pager.h"

class Reader {
public:
    void setDisplay(Display display);
    void showText(sword::SWBuf  key = "");
    void setModule(std::string module);
    void setSwordLibrary(sword::SWMgr *library);
private:
    Display display;
    Pager pager;
    std::string selectedModule;
    sword::SWMgr *swordLibrary;
    
    std::string retrieveAllKeys(sword::SWBuf key="");
};

#endif // READER_H
