/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2015-2024 its contributors. See CONTRIBUTORS file for more info
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

#ifndef INTERFACE_H
#define INTERFACE_H

//C++ Standard/STL includes
#include <string>

//SWORD Project includes
#include <swmgr.h>

//BIBISH includes
#include "../back/library.h"
#include "../back/types.h"
#include "../front/display.h"

class Interface {
    public:
        int runInterface();

    private:
        void initalize();
        void configScreen();

        validCommands processCommand(Command parsedCommand);
        
        void commandShow(Command parsedCommand);
        void commandList(Command parsedCommand);
        void commandSelect(Command parsedCommand);
        void commandSearch(Command parsedCommand);
        void commandRead(Command parsedCommand);
        void commandDevo(Command parsedCommand);
        void commandGloss(Command parsedCommand);

        std::string selectedVersion;

        Display display;
        Library library;

        sword::SWMgr *swordLibrary;
};

#endif // INTERFACE_H
