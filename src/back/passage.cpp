/*
 * BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
 * inspired by debian's bible package
 * Copyright (C) 2015  David Blue <yudahsshadow@gmx.com>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "passage.h"

#include <string>
#include <iostream>

#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

// void Passage::() const
// {
// 
// }
// 
// void Passage::() const
// {
// 
// }

void Passage::setReference(std::string reference) {

}

std::string Passage::getText() {
  std::string text = "";
  sword::SWMgr library(new sword::MarkupFilterMgr(sword::FMT_PLAIN));
  
  sword::SWModule *module;
  
  module = library.getModule("ESV");
  if(!module) {
    std::cerr << "ESV not found, install it in another front-end" << std::endl;
    text = "ESV not found error";
    return text;
  }
  
  module->setKey("Ps 1-2");
  module->renderText();
  
  text = module->getKeyText();
  text += module->renderText();
  
  return text;
  
}
