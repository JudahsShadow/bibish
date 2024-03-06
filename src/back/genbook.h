/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2023-2024  David Blue <yudahsshadow@gmx.com>
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

#ifndef GENBOOK_H
#define GENBOOK_H

//STL Includes
#include <string>

//SWORD Project Includes
#include <swmgr.h>
#include <treekey.h>
#include <swmodule.h>

#include "../back/types.h"
#include "../front/pager.h"


class Genbook
{
public:
    void setSwordLibrary(sword::SWMgr *swordLib);
    void setModule(std::string module);

    std::string getTOC();

    std::string getText(std::string key);

private:
    sword::SWMgr *swordLibrary;
    sword::SWModule *mod;
    std::string book;
    std::string toc;

    void walkTree(sword::TreeKey *treeKey);
};

#endif // GENBOOK_H

