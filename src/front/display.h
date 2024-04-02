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

#ifndef DISPLAY_H
#define DISPLAY_H

//STL Includes
#include <list>

//Project Includes
#include "../back/types.h"
#include "../front/pager.h"

class Display {
    public:
        void displayHeader();
        void displayPrompt();
        void displaySpacer(int spacing = 0);
        void displayHelp();
        void displayAbout();
        void clearScreen();
        void setHeight(uint size);
        uint getHeight();
        void setWidth(uint size);
        uint getWidth();
        void displayPages(std::list<page> text);
        void displayPercentage(uint percent);
    private:
        uint screenHeight;
        uint screenWidth;

};

#endif // DISPLAY_H
