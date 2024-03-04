/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2023  David Blue <yudahsshadow@gmx.com>
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

#include <swmgr.h>

#include <string>

#include "../back/types.h"
#include "../front/pager.h"
#include "swmodule.h"

class Genbook
{
public:
    void setSwordLibrary(sword::SWMgr *swordLib);
    void setModule(std::string module);

    std::string getTOC();

private:
    sword::SWMgr *swordLibrary;
    std::string book;
};

#endif // GENBOOK_H

