/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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

#ifndef PASSAGE_H
#define PASSAGE_H

#include <string>

#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

class Passage {
    public:
        std::string getText(std::string reference);
        void setVersion(std::string version);
        void setLibrary(sword::SWMgr *library);
    private:
        std::string version;
        sword::SWMgr *swordLibrary;
};

#endif // PASSAGE_H
