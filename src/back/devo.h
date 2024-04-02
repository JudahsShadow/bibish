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
#ifndef DEVO_H
#define DEVO_H

//STL Includes
#include <string>

//SWORD Project Includes
#include <swmgr.h>
#include <swmodule.h>

class Devo
{
public:
    void setSwordLibrary(sword::SWMgr *swordLib);
    void setDevotion(std::string module);

    std::string getDevo(std::string date);

private:
    sword::SWMgr *swordLibrary;
    sword::SWModule *devotional;
    std::string mod;
};

#endif // DEVO_H
