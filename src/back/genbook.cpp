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

#include <swmgr.h>
#include <treekey.h>
#include <swmodule.h>

#include <string>
#include <iostream>

#include "../front/pager.h"
#include "../back/types.h"
#include "../back/library.h"

#include "../back/genbook.h"

void Genbook::setSwordLibrary(sword::SWMgr *swordLib) {
    this->swordLibrary = swordLib;

}

std::string Genbook::getTOC() {
    sword::TreeKey *defaultKey;

    this->mod = swordLibrary->getModule(this->book.c_str());

    defaultKey = dynamic_cast<sword::TreeKey*>(this->mod->getKey());

    this->walkTree(defaultKey);

    return toc;
}

void Genbook::setModule(std::string module) {
    book = module;
}

void Genbook::walkTree(sword::TreeKey *treeKey) {
    if(treeKey->firstChild()) {
        while(treeKey->nextSibling()) {
            toc += treeKey->getText();
            //Add a space after the new line for the tokenizer to split on
            toc += "\n ";
            if(treeKey->hasChildren()) {
                this->walkTree(treeKey);
            }
        }
        treeKey->parent();
    }
}

