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

#ifndef GLOSS_H
#define GLOSS_H

//STL Includes
#include <string>

//SWORD Includes
#include <swmgr.h>
#include <swmodule.h>

class Gloss
{
public:
    void setSwordLibrary(sword::SWMgr *swordLib);
    void setGlossary(std::string gloss);
private:
    sword::SWMgr *swordLibrary;
    std::string toLang;
    std::string fromLang;
    sword::SWModule glossary;
};

#endif // GLOSS_H
