/*
 *BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by Debian's bible package
 * Copyright (C) 2024  David Blue <yudahsshadow@gmx.com>
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

//STL Includes
#include <string>
#include <iostream>

//SWORD Project Includes
#include <swmgr.h>
#include <treekey.h>
#include <swmodule.h>
#include <swkey.h>

//Project Includes
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
    this->book = module;
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

std::string Genbook::getText(std::string key) {
    std::string text;

    this->mod = swordLibrary->getModule(this->book.c_str());

    this->mod->setKey(key.c_str());
    text += this->mod->getKeyText();
    text += "\n";
    text += this->mod->stripText();

    return text;
}
