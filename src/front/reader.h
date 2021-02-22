/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2021  David Blue <yudahsshadow@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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

//Project Includes
#include "display.h"
#include "pager.h"

class Reader {
public:
    void setDisplay(Display display);
    void showText(std::string key = "");
    void setModule(std::string module);
private:
    Display display;
    Pager pager;
    std::string selectedModule;
};

#endif // READER_H