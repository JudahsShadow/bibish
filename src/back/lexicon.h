/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2021-2024  David Blue <yudahsshadow@gmx.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LEXICON_H
#define LEXICON_H

//STL Includes
#include <string>

//SWORD Project Includes
#include <swmgr.h>

class Lexicon
{
public:
    void setDict(std::string module);
    
    std::string getEntry(std::string entry);

    void setSwordLibrary(sword::SWMgr *swordLib);
    
private:

    sword::SWMgr *swordLibrary;
    std::string lexiDict;
};

#endif // LEXICON_H
